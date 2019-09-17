//
// Created by wangkaikai on 19-6-8.
//
#include "EventLoop.h"
#include "Util.h"
#include "MutexLock.h"
#include <iostream>
#include <sys/eventfd.h>
using namespace std;

/**
 * __thread 注意是两个横线
 * __thread变量是每个线程有一份独立实体，各个线程的变量值互不干扰。除了这个用途，他还可以修饰那些
 * “值可能会变，带有全局性，但是又不值得用全局锁保护”的变量
 */
__thread EventLoop * t_loopInthisThread = 0;

/**
 * eventfd()创建一个“eventfd对象”，这个对象能被用户空间应用用作一个事件等待/响应机制，靠内核去响应用户空间应用事件。
 * 这个对象包含一个由内核保持的无符号64位整型计数器。这个计数器由参数initval说明的值来初始化。
 * 它的标记可以有以下属性：
 * EFD_CLOEXEC：FD_CLOEXEC，简单说就是fork子进程时不继承，对于多线程的程序设上这个值不会有错的。
 * EFD_NONBLOCK：文件会被设置成O_NONBLOCK，一般要设置。
 * EFD_SEMAPHORE：（2.6.30以后支持）支持semophore语义的read，简单说就值递减1。
 * @return
 */
int createEventFd()
{
    //设置多线程且非阻塞的eventFd
    int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        cout << "Failed in eventfd";
        abort();
    }
    return evtfd;
}
EventLoop::EventLoop()
        :looping_(false),
         poller_(new Epoll()),
         wakeupFd_(createEventFd()),
         quit_(false),
         eventHandling_(false),
         callingPendingFunctors_(false),
         threadId_(CurrentThread::tid()),
         pwakeupChannel_(new Channel(this, wakeupFd_))

{
    if(t_loopInthisThread)
    {
        cout<<"not satisfied the one thread one loop, there has another eventloop in the thread"<<endl;
    }
    else
    {
        t_loopInthisThread = this;
    }
    pwakeupChannel_->setEvent(EPOLLIN|EPOLLET);//设置当前事件监听类型为有数据可读，且使用边缘触发方式
    //注册事件处理回调函数，其实也是跟上面操作一样，设置当前事件监听类型为有数据可读，且使用边缘触发方式
    pwakeupChannel_->setReadHandler(bind(&EventLoop::handleRead,this));
    //注册新连接处理回调函数
    pwakeupChannel_->setConnHandler(bind(&EventLoop::handleConn,this));
    //将处理完的的channel对象添加到epoll树上面
    poller_->epoll_add(pwakeupChannel_,0);

}

/**
 * 注册需要监听的文件描述符，即把需要的监听的epoll_event挂到红黑树上
 * @param channel_
 * @param timeout
 */
void EventLoop::addToPoller(shared_ptr<Channel> channel_, int timeout) {
    poller_->epoll_add(channel_,timeout);
}

/**
 * 对已经有的监听文件描述符进行更新
 * @param channel_
 * @param timeout
 */
void EventLoop::updatePoller(shared_ptr<Channel> channel_, int timeout) {
    poller_->epoll_mod(channel_,timeout);
}

/**
 * 将监听的文件描述符从红黑树上删除
 * @param channel_
 */
void EventLoop::removeFromPoller(shared_ptr<Channel> channel_) {
    poller_->epoll_del(channel_);
}


/**
 * EventLoop类中定义的回调函数
 * 实际上就是更新channel对象
 */
void EventLoop::handleConn() {
    updatePoller(pwakeupChannel_,0);
}

/**
 * EventLoop处理读数据的函数
 * 设置监听事件
 */
void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = readn(wakeupFd_,&one, sizeof(one));
    if(n!= sizeof(one))
    {
        cout<<"EventLoop::handleRead()"<<n<<"bytes";
    }
    pwakeupChannel_->setEvent(EPOLLIN|EPOLLET);
}

EventLoop::~EventLoop() {

}

void EventLoop::loop() {
    assert(!looping_);
    assert(isInLoopThread());
    looping_ = true;
    quit_ = false;
    cout<<"EventLoop start"<<endl;
    vector<shared_ptr<Channel>> ChannelToAllocate;
    while (!quit_)
    {
        cout<<"start handling event"<<endl;
        ChannelToAllocate.clear();
        ChannelToAllocate = poller_->poll();
        eventHandling_ = true;
        for(auto &it:ChannelToAllocate)
        {
            it->handleEvents();//调用Channel类中的事件分发函数，分发函数再调用不同的处理函数
        }
        eventHandling_ = false;
    }

}

void EventLoop::quit() {

}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = writen(wakeupFd_,(char *)&one, sizeof(one));
    if(n!= sizeof(one))
        cout<<"EventLoop:wakeup() writes" << n << "bytes instead of 8";
}
void EventLoop::runInLoop(EventLoop::Functor &&cb) {
    ///如果是当前I/O线程调用，则直接调用这个cb()函数就好
    if(isInLoopThread())
    {
        cb();
    } else
    {
        ///std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝。
        ///如果不是当前线程，就需要将其加入到队列，这要求处理函数必须是线程安全的函数
        queueInLoop(std::move(cb));
    }
}

/**
 * 如果时EventLoop的owner线程，会调用runInLoop会立即执行回调函数cb
 * 否则会把回调函数放到任务队列（其实时vector），即调用queueInLoop函数。
 * 如果不是当前线程调用，或者正在执行pendingFunctors_中的任务，
 * 都要唤醒EventLoop的owner线程，让其执行pendingFunctors_中的任务。
 * 如果正在执行pendingFunctors_中的任务，添加新任务后不会执行新的任务，
 * 因为functors.swap(pendingFunctors_)后，执行的时functors中的任务
 * -调用queueInLoop的线程不是当前IO线程需要唤醒（当前I/O线程指的是EventLoop所属的I/O线程），A线程往B线程添加任务
 * -或者调用queueInLoop的线程是当前IO线程，并且此时正在调用pending functor，需要唤醒（doPendingFunctors内部中又调用了queueInLoop）
 * -只有IO线程的事件回调中调用queueInLoop才不需要唤醒
 * @param cb
 */

void EventLoop::queueInLoop(EventLoop::Functor &&cb) {
    ///范围内加锁,添加cb（）函数到pendingFunctors_队列中
    {
        MutexLockGuard lock(mutex_);

        pendingFunctors_.emplace_back(std::move(cb));
    }
    if(!isInLoopThread()||callingPendingFunctors_)
        wakeup();
}


/**
 * 不是简单地在临界区内依次调用Functor，而是把回调列表swap到functors中，
 * 这样一方面减小了临界区的长度（意味着不会阻塞其它线程的queueInLoop()），
 * 另一方面，也避免了死锁（因为Functor可能再次调用queueInLoop()）
 * 由于doPendingFunctors()调用的Functor可能再次调用queueInLoop(cb)，
 * 这时，queueInLoop()就必须wakeup()，否则新增的cb可能就不能及时调用了
 * muduo没有反复执行doPendingFunctors()直到pendingFunctors为空，这是有意的，
 * 否则IO线程可能陷入死循环，无法处理IO事件。
 */
void EventLoop::doPendingFunctors() {
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
        MutexLockGuard lock(mutex_);
        functors.swap(pendingFunctors_);
    }
    for (size_t i = 0; i < functors.size(); ++i)
    {
        functors[i]();
    }
    callingPendingFunctors_ = false;
}
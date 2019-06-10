//
// Created by wangkaikai on 19-6-8.
//
#include "EventLoop.h"
#include "Util.h"
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
    pwakeupChannel_->setReadHandler(bind(&EventLoop::handleRead,this));

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
 */
void EventLoop::handleConn() {

}

void EventLoop::handleRead() {

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
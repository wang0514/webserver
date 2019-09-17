//
// Created by wangkaikai on 19-6-8.
//

#ifndef WEBSERVER_EVENTLOOP_H
#define WEBSERVER_EVENTLOOP_H

#include <functional>
#include <vector>
#include <memory>
#include <iostream>
#include <assert.h>
#include "currentThreadNamespace.h"
#include "Epoll.h"
#include "MutexLock.h"

using namespace std;
class EventLoop{
public:
    typedef function<void()> Functor;
    EventLoop() ;
    ~EventLoop() ;
    void loop();
    void quit();
    void runInLoop(Functor&& cb);
    void queueInLoop(Functor&& cb);
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
    void assertInLoopThread()//确认是不是当前线程，即满足one thread one loop条件
    {
        assert(isInLoopThread());
    }
    void updatePoller(shared_ptr<Channel> channel_,int timeout = 0);
    void addToPoller(shared_ptr<Channel> channel_,int timeout = 0);
    void removeFromPoller(shared_ptr<Channel> channel_);

private:
    //private声明时为了避免与函数重名，所以代码里变量默认加上下划线
    bool looping_;//判断当前是否有循环，one thread one loop
    shared_ptr<Epoll> poller_;
    int wakeupFd_;//这是EventFd，对应的Channel是pwakeupChannel_，每个线程都有，负责线程的唤醒
    bool quit_;//EventLoop的退出标志
    bool eventHandling_;//表示是否正在处理事件
    mutable MutexLock mutex_;
    const pid_t threadId_;
    vector<Functor> pendingFunctors_;//异步调用添加的需要处理的函数
    bool callingPendingFunctors_;//是否正在调用异步调用处理的函数
    /**对应的唤醒专用的Channel，每个Thread只有这么一个Channel
     * EventLoop和Channel对象本身是一种聚合关系，也就是说一个EventLoop对象对应多个Channel对象
     * 并且这写Channel对象的生存期实际上跟EventLoop实际上没有啥关系，即EventLoop对象不用管理Channel的生存期
     * 但是pwakeupChannel_除外，这个特殊的Channel和EventLoop是一种组合关系，即一个EventLoop对象对应一个Channel对象
     */
    shared_ptr<Channel> pwakeupChannel_;


    void wakeup();
    void handleRead();
    void handleConn();
    void doPendingFunctors();//调用pendingFunctor队列中的函数

};
#endif //WEBSERVER_EVENTLOOP_H

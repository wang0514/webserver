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
using namespace std;
class EventLoop{
public:
    typedef function<void()> Functor;
    EventLoop() ;
    ~EventLoop() ;
    void loop();
    void quit();
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
    int wakeupFd_;
    bool quit_;
    bool eventHandling_;
    const pid_t threadId_;
    vector<Functor> pendingFunctors_;
    bool callingPendingFunctors_;
    shared_ptr<Channel> pwakeupChannel_;

    void wakeup();
    void handleRead();
    void handleConn();


};
#endif //WEBSERVER_EVENTLOOP_H

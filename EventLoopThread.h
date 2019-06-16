//
// Created by wangkaikai on 19-6-14.
//

#ifndef WEBSERVER_EVENTLOOPTHREAD_H
#define WEBSERVER_EVENTLOOPTHREAD_H

#include "EventLoop.h"
#include "Thread.h"

class EventLoopThread{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

private:
    void threadFunc();
    EventLoop *loop_;
    bool exiting_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
};
#endif //WEBSERVER_EVENTLOOPTHREAD_H

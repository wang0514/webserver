//
// Created by wangkaikai on 19-6-15.
//

#ifndef WEBSERVER_EVENTLOOPTHREADPOOL_H
#define WEBSERVER_EVENTLOOPTHREADPOOL_H

#include "noncopyable.h"
#include "EventLoop.h"
#include "EventLoopThread.h"

class EventLoopThreadPool: noncopyable
{
public:
    EventLoopThreadPool(EventLoop *baseLoop, int numThreads);

    ~EventLoopThreadPool();
    void start();
    EventLoop* getNextLoop();


private:
    EventLoop *baseLoop_;
    bool started_;//线程池开启标志
    int numThreads_;//线程数量
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;//用来存储线程池的
    std::vector<EventLoop*> loops_;//用来存储线程对应的EventLoop事件的

};
#endif //WEBSERVER_EVENTLOOPTHREADPOOL_H

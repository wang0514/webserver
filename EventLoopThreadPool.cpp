//
// Created by wangkaikai on 19-6-15.
//

#include "EventLoopThreadPool.h"

/**
 * 线程池构造函数
 * 一个EventLoop事件，线程池中线程的个数
 * @param baseLoop
 * @param numThreads
 */
EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, int numThreads) :
        baseLoop_(baseLoop),
        numThreads_(numThreads),
        started_(false),
        next_(0)
{
    if(numThreads_<=0)
    {
        cout<<"not enough Threads"<<endl;
        abort();
    }
}

EventLoopThreadPool::~EventLoopThreadPool() {

}

/**
 * 线程池开启函数
 * 分配的线程放到threads_数组中
 * 对用的EventLoop事件放到loops_数组中
 */
void EventLoopThreadPool::start() {
    baseLoop_->assertInLoopThread();//确认是不是当前线程，即满足one thread one loop条件
    started_ = true;
    for(int i =0;i<numThreads_;++i )
    {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        threads_.push_back(t);
        loops_.push_back(t->startLoop());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop() {
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop *loop = baseLoop_;
    if(!loops_.empty())
    {
        loop = loops_[next_];
        next_ = (next_+1)%numThreads_;
    }
    return loop;
}
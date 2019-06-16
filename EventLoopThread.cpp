//
// Created by wangkaikai on 19-6-14.
//

#include "EventLoopThread.h"

/**
 * EventLoopThread的构造函数
 * 主要是注册一下回调函数，使用EventLoopThread中的threadFunc函数作为线程的传入参数
 * 另外要注册一个锁，相对应的注册一个条件变量
 */
EventLoopThread::EventLoopThread():
        loop_(NULL),
        exiting_(false),
        thread_(bind(&EventLoopThread::threadFunc,this),"EventLoopThread"),
        mutex_(),
        cond_(mutex_)
{}

/**
 * EventLoopThread的析构函数
 * 退出标志设置为true
 * 调用loop_的quit（）函数
 * Thread类开启join（）操作
 */
EventLoopThread::~EventLoopThread() {
    exiting_ = true;
    if(loop_!=NULL)
    {
        loop_->quit();
        thread_.join();
    }
}

/**
 * 事件循环开启函数
 * 创建线程，然后返回Eventloop事件，这里面一个EventLoop事件对应一个thread
 * one loop one thread具体体现可能在在这里
 * @return
 */
EventLoop* EventLoopThread::startLoop() {
    assert(!thread_.started());//先确认一下线程是否开起来了
    thread_.start();//创建线程

    {
        MutexLockGuard lock(mutex_);
        //这一步的目的是为了threadFun在Thread中真正跑起来
        while(loop_==NULL)
            cond_.wait();
    }
    return loop_;
}

/**
 * 需要传进线程的实际函数
 * 实际上就是把EventLoop的loop（）函数传进去
 */
void EventLoopThread::threadFunc() {
    EventLoop loop;

    {
        MutexLockGuard lock(mutex_);//加锁
        loop_ = &loop;
        cond_.notify();
    }

    loop_->loop();

    loop_=NULL;
}
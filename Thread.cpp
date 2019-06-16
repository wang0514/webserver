//
// Created by wangkaikai on 19-6-11.
//

#include "Thread.h"
#include "currentThreadNamespace.h"
#include <sys/prctl.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <stdint.h>
#include <unistd.h>


#include <iostream>
#include <assert.h>

using namespace std;

namespace CurrentThread
{
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread int t_tidStringLength = 6;
    __thread const char* t_threadName = "default";
}

pid_t gettid()
{
    return static_cast<pid_t>(::syscall(SYS_getpid));//TODO 没搞懂为啥要加作用域指定
}

void CurrentThread::cacheTid() {
    if(t_cachedTid==0)
    {
        t_cachedTid = gettid();
        t_tidStringLength = snprintf(t_tidString, sizeof(t_tidString),"%5d",t_cachedTid);
    }
}
/**
 * 使用了一个中间结构，ThreadData，装载了我们希望赋予副线程的名字，
 * 希望从副线程那里取回的tid指针，还有我们希望它执行的函数。
 * startThread是一个外部的函数，用来调用ThreadData的runInThread，
 * 因为pthread_create只接受静态函数，所以我们需要一个跳板，这边是startThread存在的意义。
 * runInThread里我们修改线程名字，获取线程tid的值，运行fun。
 */
struct ThreadData
{
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;
    string name_;
    pid_t* tid_;
    CountDownLatch* latch_;

    ThreadData(const ThreadFunc &func, const string& name, pid_t *tid, CountDownLatch *latch)
            :   func_(func),
                name_(name),
                tid_(tid),
                latch_(latch)
    {}

    void runInThread(){
        *tid_ = CurrentThread::tid();
        tid_ = NULL;
        latch_->countDown();
        latch_= NULL;
        CurrentThread::t_threadName = name_.empty()?"Thread" : name_.c_str();
        prctl(PR_SET_NAME,CurrentThread::t_threadName);//修改线程的名字

        func_();
        CurrentThread::t_threadName = "finished";
    }
};

void *startThread(void* obj)
{
    ThreadData* data = static_cast<ThreadData*>(obj);
    data->runInThread();
    delete data;
    return NULL;
}

/**
 * Thread的构造函数，需要完成线程入口函数的指定，线程的名字
 * 以及线程的状态
 * @param func
 * @param n
 */
Thread::Thread(const Thread::ThreadFunc &func, const std::string &n)
        :started_(false),
         joined_(false),
         pthereadId_(0),
         tid_(0),
         func_(func),
         name_(n),
         latch_(1)
{
    setDefaultName();
}

Thread::~Thread() {
    if(started_&&!joined_)
        pthread_detach(pthereadId_);
}

void Thread::setDefaultName() {
    if(name_.empty())
    {
        char buf[32];
        snprintf(buf, sizeof(buf),"thread");
    }
}

/**
 * 开启线程，要把ThreadData这个结构体作为传入参数传进去
 * 且需要检查latch_
 * 这一步是要保证传进去的函数确实被运行了
 */
void Thread::start() {
    assert(!started());
    started_ = true;
    ThreadData *data = new ThreadData(func_,name_,&tid_,&latch_);
    if(pthread_create(&pthereadId_,NULL,startThread,data))
    {
        started_ = false;
        delete data;
    } else
    {
        latch_.wait();
        assert(tid_>0);
    }

}

int Thread::join() {
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pthereadId_,NULL);
}
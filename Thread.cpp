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
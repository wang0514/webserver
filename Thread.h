//
// Created by wangkaikai on 19-6-11.
//

#ifndef WEBSERVER_THREAD_H
#define WEBSERVER_THREAD_H

#include "CountDownLatch.h"
#include "noncopyable.h"
#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>

class Thread : noncopyable
{
public:
    typedef std::function<void()> ThreadFunc;//线程入口函数
    explicit Thread(const ThreadFunc&, const std::string&name = std::string());
    ~Thread();
    void start();
    int join();
    bool started() const{
        return started();
    }
    pid_t tid() const{
        return tid_;
    }

private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthereadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;

};


#endif //WEBSERVER_THREAD_H

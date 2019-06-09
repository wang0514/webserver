//
// Created by wangkaikai on 19-6-8.
//

#ifndef WEBSERVER_EVENTLOOP_H
#define WEBSERVER_EVENTLOOP_H

#include <functional>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;
class EventLoop{
public:
    typedef function<void()> Functor;
    EventLoop() ;
    ~EventLoop() ;
    void loop();
    void quit();


private:
    //private声明时为了避免与函数重名，所以代码里变量默认加上下划线
    bool looping_;//判断当前是否有循环，one thread one loop
    //shared_ptr<Epoll> poller_;
    int wakeupFd_;
    bool quit_;
    bool eventHandling_;
    const pid_t threadId_;

    void wakeup();
    void handleRead();
    void handleConn();


};
#endif //WEBSERVER_EVENTLOOP_H

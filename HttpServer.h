//
// Created by wangkaikai on 19-6-16.
//

#ifndef WEBSERVER_HTTPSERVER_H
#define WEBSERVER_HTTPSERVER_H

#include "EventLoop.h"
#include "EventLoopThreadPool.h"

class HttpServer{
public:
    HttpServer(EventLoop *loop, int threadNum, int port);

    ~HttpServer();
    EventLoop* getLoop() const { return loop_;}
    void start();
    void handleNewConn();
    void handleThisConn()
    {
        loop_->updatePoller(acceptChannel_);
    }



private:
    EventLoop *loop_;
    int threadNum_;
    std::unique_ptr<EventLoopThreadPool> EventLoopThreadPool_;
    bool started_;
    std::shared_ptr<Channel> acceptChannel_;
    int port_;
    int listenfd_;
    static const int MAXFDS = 100000;
};

#endif //WEBSERVER_HTTPSERVER_H

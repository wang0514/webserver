//
// Created by wangkaikai on 19-6-9.
//

#ifndef WEBSERVER_CHANNEL_H
#define WEBSERVER_CHANNEL_H


#include <functional>
#include <sys/epoll.h>

class EventLoop;

class Channel{
public:
    Channel(EventLoop *loop);
    Channel(EventLoop *loop,int fd);
    ~Channel();
    int getfd();
    void setfd(int fd);

    __uint32_t events_;
    __uint32_t revents_;//epoll_event中的event属性
    __uint32_t lastEvents_;

private:
    typedef std::function<void()> Callback;
    EventLoop *loop_;
    int fd_;//对应的EventLoop对象中的wakeupFd_,这个FD是用eventfd函数生成的非阻塞文件描述符

    Callback readHandler_;
    Callback writeHandler_;
    Callback errorHandler_;
    Callback connHandler_;

public:
    /**
     * 外层的回调函数就是从这里进来的
     * 然后分别对应的函数处理
     * @param Handler
     */
    void setReadHandler(Callback &&readHandler)
    {
        readHandler_ = readHandler;
    }

    void setWriteHandler(Callback &&writeHandler)
    {
        writeHandler_ = writeHandler;
    }

    void setErrorHandler(Callback &&errorHandler)
    {
        errorHandler_ = errorHandler;
    }

    void setConnHandler(Callback &&connHandler)
    {
        connHandler_ = connHandler;
    }

    void handleEvents();
    void handleRead();
    void handleWrite();
    void handleError();
    void handleConn();

    void setRevents(__uint32_t ev);
    void setEvent(__uint32_t ev);
    /**
     * 返回引用类型：当函数返回引用类型时，没有复制返回值，相反，返回的是对象本身。
     * 千万不要返回局部对象的引用！千万不要返回指向局部对象的指针！
     * @return
     */
    __uint32_t& getEvents();
    bool EqualAndUpdateEvents();
    __uint32_t getLastEvent();


};
#endif //WEBSERVER_CHANNEL_H

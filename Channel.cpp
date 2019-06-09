//
// Created by wangkaikai on 19-6-9.
//

#include "Channel.h"
#include "EventLoop.h"
/**
 * Channel类的构造函数，不带fd
 * @param loop
 */
Channel::Channel(EventLoop *loop) :
        loop_(loop),
        events_(0),
        lastEvents_(0)
        {}

/**
 * Channel类的构造函数，带fd
 * @param loop
 * @param fd
 */
Channel::Channel(EventLoop *loop, int fd) :
        loop_(loop),
        fd_(fd),
        events_(0),
        lastEvents_(0) {}

/**
 * Channel类的析构函数
 */
Channel::~Channel() {}

/**
 * 返回fd_
 * @return
 */

int Channel::getfd() {
    return fd_;
}

/**
 * 设置fd_
 * @param fd
 */
void Channel::setfd(int fd) {
    fd_ =fd;
}

/**
 * 针对传过来的事件做处理
 * 分别对应读操作，写操作，连接操作
 */
void Channel::handleEvents() {
    events_ = 0;
    /**
     * EPOLLHUP：这个好像有些系统检测不到，可以使用EPOLLIN，read返回0，删除掉事件，关闭close(fd);
     * 如果有EPOLLRDHUP，检测它就可以知道是对方关闭；否则就用上面方法。
     * 此时应该是对方关闭客户端连接，且当前事件没有数据要读
     * 直接返回
     */
     //表示客户端已经断开连接，且没有数据可以读
     if((revents_ & EPOLLHUP)&&!(revents_&EPOLLIN)){
         events_ = 0;
         return;
     }
     //表示客户端有数据可读、断开连接或者发生异常情况
     if(revents_&(EPOLLIN|EPOLLPRI|EPOLLHUP))
     {
         handleRead();
     }
     if(revents_&EPOLLOUT)
     {
         handleWrite();
     }
     handleConn();
}

/**
 * 处理读操作
 */
void Channel::handleRead() {
    if(readHandler_)
    {
        readHandler_();
    }
}

/**
 * 处理写操作
 */
void Channel::handleWrite() {
    if(writeHandler_)
    {
        writeHandler_();
    }
}

/**
 * 错误处理
 */
void Channel::handleError() {
    if(errorHandler_)
    {
        errorHandler_();
    }
}

/**
 * 连接处理
 */
void Channel::handleConn() {
    if(connHandler_)
    {
        connHandler_();
    }
}

/**
 * 设置需要处理的事件的epoll_event中的event属性
 * @param ev
 */
void Channel::setRevents(__uint32_t ev) {
    revents_ = ev;
}

//TODO 好像这里面的epoll_event都是给到0，具体作用不清楚，在handleEvent（）中有使用
void Channel::setEvent(__uint32_t ev) {
    events_ = ev;
}


__uint32_t& Channel::getEvents() {
    return events_;
}

/**
 * 判断上一次事件的类型和这次是否相同，返回
 * 并且将lastEvents_更新为现在的events_
 * @return
 */
bool Channel::EqualAndUpdateEvents() {
    bool ret = (lastEvents_==events_);
    lastEvents_ = events_;
    return ret;
}

/**
 * 返回上一次的事件类型
 * @return
 */
__uint32_t Channel::getLastEvent() {
    return lastEvents_;
}
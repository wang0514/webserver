//
// Created by wangkaikai on 19-6-9.
//

#ifndef WEBSERVER_EPOLL_H
#define WEBSERVER_EPOLL_H

#include <memory>
#include <vector>
//#include <sys/epoll.h>
#include "Channel.h"

using namespace std;
class Epoll{
public:
    Epoll();
    ~Epoll();
    vector<shared_ptr<Channel>> poll();//调用epoll_wait()阻塞等待事件发生
    //将epoll_wait()的传出数组放进Channel数组里面
    vector<shared_ptr<Channel>> getRequest(int event_active);
    int getEpollFd()
    {
        return epollFd_;
    }

private:
    static const int MAXFDS = 100000; //最大处理的文件描述符个数
    int epollFd_;//epoll文件描述符
    std::vector<epoll_event> events_;//就绪队列，也就是epoll_wait的传出参数
    /**
     * 光有fd不够，要把fd转换成Channel，这就是封装的思想
     * fdToChannel_数组最大值为MAXFDS,也就是说channel类默认生成一个包含MAXFDS个元素的channel对象数组
     * 要处理的操作也是针对这个数组中的元素进行的
     */
    std::shared_ptr<Channel> fdToChannel_[MAXFDS];


};
#endif //WEBSERVER_EPOLL_H

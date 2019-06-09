//
// Created by wangkaikai on 19-6-9.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <assert.h>
#include <iostream>

#define EVENTSUM 4096
#define EPOLLWAIT_TIME 10000

Epoll::Epoll() :
        epollFd_(epoll_create1(EPOLL_CLOEXEC)),
        events_(EVENTSUM) {
    assert(epollFd_);
}

Epoll::~Epoll()
{

}

/**
 * 返回活跃事件的数组
 * @return
 */
vector<shared_ptr<Channel>> Epoll::poll() {

    while(1) {
        //注意，这里的迭代器要先取出元素再取地址，不然会报错
        int event_active = epoll_wait(epollFd_, &*events_.begin(), events_.size(), EPOLLWAIT_TIME);
        if(event_active<0)
            perror("epoll_wait error\n");
        vector<shared_ptr<Channel>> ret = getRequest(event_active);
        //得到需要被处理的channel对象数组
        if(ret.size())
            return ret;
    }

}

/**
 * 这是分发处理函数
 * @param event_active
 * @return
 */
std::vector<shared_ptr<Channel>> Epoll::getRequest(int event_active) {
    std::vector<shared_ptr<Channel>> event_data;
    for(int i = 0;i<event_active;++i)
    {
        //得到传出数组对应的文件描述符
        int fd = events_[i].data.fd;
        shared_ptr<Channel> cur_event_data = fdToChannel_[fd];
        if(cur_event_data)
        {
            /**
             * 把epoll_wait得到的文件描述符设置到Channel类对象中
             */
            cur_event_data->setRevents(fd);
            //TODO 为什么events_要设置为0
            cur_event_data->setEvent(0);
            //将配置好的channel对象放进需要处理的channel数组中
            event_data.push_back(cur_event_data);
        }
        else
        {
            std::cout<<"shared_ptr cur_event_data is invalid"<<std::endl;
        }
    }
    return event_data;
}
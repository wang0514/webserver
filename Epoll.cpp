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
        if(ret.size()>0)
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


//TODO 实现添加epoll_event的操作
void Epoll::epoll_add(shared_ptr<Channel> channel_, int timeout) {
    int fd = channel_->getfd();
    if(timeout>0)
    {
        //TODO 计时器信息处理
    }
    struct epoll_event event;
    event.data.fd = fd;
    event.events = channel_->getEvents();
    channel_->EqualAndUpdateEvents();
    fdToChannel_[fd] = channel_;
    int ret = epoll_ctl(epollFd_,EPOLL_CTL_ADD,fd,&event);
    if(ret<0)
    {
        perror("epoll_ctl add error\n");
        fdToChannel_[fd].reset();//释放shared_ptr的管理权限
    }
}


//TODO 实现epoll_event 中event事件的修改和更新
void Epoll::epoll_mod(shared_ptr<Channel> channel_, int timeout) {
    if(timeout>0)
    {
        //TODO timer设置

    }
    int fd = channel_->getfd();
    if(!channel_->EqualAndUpdateEvents())//只在和上一次事件类型不一致时才更新
    {
        struct epoll_event event;
        event.events = channel_->getEvents();
        event.data.fd = fd;
        int ret = epoll_ctl(epollFd_,EPOLL_CTL_MOD,fd,&event);
        if(ret<0)
        {
            perror("epoll_ctl mod error\n");
            fdToChannel_[fd].reset();
        }
    }

}

//TODO 实现epoll_event的删除操作
void Epoll::epoll_del(shared_ptr<Channel> channel_) {
    int fd = channel_->getfd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = channel_->getEvents();
    event.events = channel_->getLastEvent();
    if(epoll_ctl(epollFd_,EPOLL_CTL_DEL,fd,&event)<0)
    {
        perror("epoll_ctl del error\n");
    }
    fdToChannel_[fd].reset();
}
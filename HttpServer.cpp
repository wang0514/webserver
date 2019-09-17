//
// Created by wangkaikai on 19-6-16.
//
/**
 * HttpServer构造函数利用拷贝构造函数传入了一个EventLoop类型
 * 同时也有一个Channel类型，还有一个线程池
 * handleNewConn()函数从线程池里面取得了下一个EventLoop事件
 */

#include <cstring>
#include "HttpServer.h"
#include "Util.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


/**
 * httpserver的构造函数
 * 主要完成下面几个功能：
 * 1.给定EventLoop事件，线程数量，端口号
 * 2.根据给定的端口号生成相应的监听fd，即listenfd_；
 * 3.生成一个对应的Channel事件，一个对应的线程池
 * 4.设置监听文件描述符为非阻塞方式监听
 * 5.设置底层的Channel—事件的文件描述符属性为listenfd_
 * @param loop
 * @param threadNum
 * @param port
 */
HttpServer::HttpServer(EventLoop *loop, int threadNum, int port) :
        loop_(loop),
        threadNum_(threadNum),
        port_(port),
        started_(false),
        listenfd_(socket_bind_listen(port)),
        acceptChannel_(new Channel(loop_)),
        EventLoopThreadPool_(new EventLoopThreadPool(loop_,threadNum))
{
    acceptChannel_->setfd(listenfd_);
    handle_for_sigpipe();
    if(setSocketNonBlocking(listenfd_)<0)
    {
        perror("set socket_nonblock error\n");
        abort();
    }

}

HttpServer::~HttpServer() {

}

/**
 * httpserver处理新连接的方式
 * 循环接受监听描述符事件，并且从线程池得到一个新的EventLoop事件
 * 后面将这个new出来的EventLoop和acceptfd_传到HttpData
 */
void HttpServer::handleNewConn() {
    struct sockaddr_in client_addr;//设置客户端的地址，作为accept的传出参数
    memset(&client_addr,0, sizeof(client_addr));
    socklen_t client_len = sizeof(sockaddr_in);
    int accept_fd = 0;
    while((accept_fd = accept(listenfd_,(struct sockaddr*)&client_addr,&client_len))>0)
    {
        ///轮询法确定监听到的文件描述符交给哪一个EventLoopThread处理
        /// 从EventLoopThreadPool_线程池里面得到一个新的EventLoop事件
        EventLoop* loop = EventLoopThreadPool_->getNextLoop();
        cout<<"client address :"<<inet_ntoa(client_addr.sin_addr)<<endl;
        cout<<"port:"<<ntohs(client_addr.sin_port);

        //设置服务器的最大并发连接数
        if(accept_fd>=MAXFDS)
        {
            close(accept_fd);
            continue;
        }

        //设置非阻塞接收模式
        if(setSocketNonBlocking(accept_fd)<0)
        {
            perror("setSocketNonBlocking error\n");
            return;
        }

        ///禁用Nagle算法
        setSocketNodelay(accept_fd);

        //TODO 关于HttpRequest的操作
        /**
         *将接收到的accept_fd和对应的loop事件封装到HttpData类中，后续处理这个HttpData
         * HttpData这个类和eventLoop对象也是聚合关系
         */
        shared_ptr<HttpData> req_info(new HttpData(loop,accept_fd));
        req_info->getChannel()->setHolder(req_info);
        /**
         * 跨线程调用，也就是主Reactor将新任务添加到SubReactor中进行处理，这里是一个异步调用
         * 因为不是当前线程调用这个处理函数，queueInLoop会将这个函数添加到pendingFunctors_队列
         * 紧接着唤醒loop所在EventLoop，也就是往loop对应的EventLoop对象中的EventFd写一个byte的数据
         */
         loop->queueInLoop(std::bind(&HttpData::newEvent,req_info));
    }
    acceptChannel_->setEvent(EPOLLIN|EPOLLET);
}

/**
 * HttpServer的开启函数
 * 主要功能五个：
 * 1.开启线程池；
 * 2.设置监听Channel的属性
 * 3.将channel的读处理操作绑定到HttpServer的handleNewConn函数上
 * 4.将channel的连接处理绑定到HttpServer的handleThisConn函数上
 * 5.将loop_挂到epoll树上
 */
void HttpServer::start() {
    /**
     * 开启线程池的操作，生成threadNum个线程，每个线程在EventLoopThread对象中，
     * 且有一个Thread数组和一个EventLoop数组存储这些内容
     * 每个创建好的线程都在处于pooler状态，且初始化的线程只有对应的EventFd描述符
     */
    EventLoopThreadPool_->start();
    acceptChannel_->setEvent(EPOLLIN|EPOLLET);
    acceptChannel_->setReadHandler(bind(&HttpServer::handleNewConn,this));//注册acceptChannel_处理新连接函数
    acceptChannel_->setConnHandler(bind(&HttpServer::handleThisConn,this));//注册acceptChannel_处理当前连接函数
    loop_->updatePoller(acceptChannel_,0);//将acceptChannel加入epoll检测，这是mainReactor
    started_ = true;
}
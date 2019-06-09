//
// Created by wangkaikai on 19-5-31.
//
#include <string>
#include <iostream>
#include "EventLoop.h"

#define LOG_PATH_DEFAULT "./webserver.log"
int main(int argv,char *argc[])
{
    int port = 3000;//端口默认给3000
    std::string logpath = LOG_PATH_DEFAULT;//日志的默认路径
    std::cout<<"LOG PATH is"<<logpath<<std::endl;
    EventLoop mainloop;

}




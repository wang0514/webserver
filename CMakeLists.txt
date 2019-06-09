cmake_minimum_required(VERSION 3.14)
project(webserver)

set(CMAKE_CXX_STANDARD 14)

add_executable(webserver main.cpp EventLoop.cpp EventLoop.h currentThreadNamespace.h Util.cpp Util.h Epoll.cpp Epoll.h Channel.cpp Channel.h)

find_package(Threads REQUIRED)
target_link_libraries(webserver Threads::Threads)
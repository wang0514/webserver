cmake_minimum_required(VERSION 3.14)
project(webserver)

set(CMAKE_CXX_STANDARD 14)

add_executable(webserver main.cpp EventLoop.cpp EventLoop.h)
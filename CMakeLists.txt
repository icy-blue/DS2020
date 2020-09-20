cmake_minimum_required(VERSION 3.16)
project(DS2020)

set(CMAKE_CXX_STANDARD 17)

add_executable(DS2020 main.cpp LinkedList.cpp LinkedList.h Stack.cpp Stack.h Queue.cpp Queue.h pair.cpp pair.h)
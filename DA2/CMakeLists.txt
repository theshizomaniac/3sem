cmake_minimum_required(VERSION 3.6)
project(DA2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp rbtree.h rbtree.cpp)
add_executable(DA2 ${SOURCE_FILES})
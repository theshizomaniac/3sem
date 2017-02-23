cmake_minimum_required(VERSION 3.6)
project(DA4_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lab.cpp)
add_executable(DA4_2 ${SOURCE_FILES})
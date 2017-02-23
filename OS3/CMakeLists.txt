cmake_minimum_required(VERSION 3.6)
project(OS3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lab.c)
add_executable(OS3 ${SOURCE_FILES})
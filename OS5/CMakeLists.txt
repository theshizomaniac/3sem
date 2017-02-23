cmake_minimum_required(VERSION 3.6)
project(OS5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    mylib.c
    mylib.h
    test.c TList.h TList.c listest.c dlist.c)

add_executable(OS5 ${SOURCE_FILES})
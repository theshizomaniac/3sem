cmake_minimum_required(VERSION 3.6)
project(OS6)
FIND_LIBRARY(ZMQ_LIB libzmq)
TARGET_LINK_LIBRARIES(myExecOrLib ${ZMQ_LIB})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp client_ex.c server_ex.c cl_ex.c ser_ex.c TVector.h TVector.c async-s-c.c server.c hb_server.c hb_workers.c hb_collector.c)
add_executable(OS6 ${SOURCE_FILES})
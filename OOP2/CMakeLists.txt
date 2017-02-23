cmake_minimum_required(VERSION 3.6)
project(OOP2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TArray.h TArray.cpp Rectangle2.h Rectangle2.cpp)
add_executable(OOP2 ${SOURCE_FILES})
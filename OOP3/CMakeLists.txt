cmake_minimum_required(VERSION 3.6)
project(OOP3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Rectangle.h Tarray.cpp Tarray.h TArrayItem.h Rectangle.cpp Trapeze.cpp Trapeze.h Rhomb.cpp Rhomb.h)
add_executable(OOP3 ${SOURCE_FILES})
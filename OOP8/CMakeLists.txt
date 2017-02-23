cmake_minimum_required(VERSION 3.6)
project(OOP8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp TArrayItem.h Rectangle.cpp Rectangle.h Rhomb.cpp Rhomb.h Trapeze.cpp Trapeze.h TemplateArray.h TIterator.h TAllocator.cpp TAllocator.h TArrayItem.cpp)
add_executable(OOP8 ${SOURCE_FILES})
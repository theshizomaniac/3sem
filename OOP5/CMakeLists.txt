cmake_minimum_required(VERSION 3.6)
project(OOP5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TArray.h TArray.cpp TArrayItem.h Rectangle.cpp Rectangle.h Rhomb.cpp Rhomb.h Trapeze.cpp Trapeze.h TemplateArray.h TIterator.h)
add_executable(OOP5 ${SOURCE_FILES})
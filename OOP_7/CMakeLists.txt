cmake_minimum_required(VERSION 3.6)
project(OOP_7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TArrayItem.h Rectangle.cpp Rectangle.h Rhomb.cpp Rhomb.h Trapeze.cpp Trapeze.h TemplateArray.h TIterator.h TAllocator.cpp TAllocator.h TArrayItem.cpp TBinaryTree.h TNode.h)
add_executable(OOP_7 ${SOURCE_FILES})
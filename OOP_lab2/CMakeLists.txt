cmake_minimum_required(VERSION 3.6)
project(OOP_lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Hexagon.h Hexagon.cpp TreeNode.h Tree.cpp TreeNode.cpp Tree.h)
add_executable(OOP_lab2 ${SOURCE_FILES})
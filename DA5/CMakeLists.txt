cmake_minimum_required(VERSION 3.6)
project(DA5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Ukkonen-SuffixTree/createInput.cpp
    Ukkonen-SuffixTree/edge.cpp
    Ukkonen-SuffixTree/edge.h
    Ukkonen-SuffixTree/node.cpp
    Ukkonen-SuffixTree/node.h
    Ukkonen-SuffixTree/suffixTree.cpp
    Ukkonen-SuffixTree/suffixTree.h
        suffixTr.cpp)

add_executable(DA5 ${SOURCE_FILES})
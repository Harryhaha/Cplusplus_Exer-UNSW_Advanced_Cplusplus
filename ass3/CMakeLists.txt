cmake_minimum_required(VERSION 3.6)
project(comp6771_ass3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES Graph.cpp Graph.h)
add_executable(comp6771_ass3 ${SOURCE_FILES})
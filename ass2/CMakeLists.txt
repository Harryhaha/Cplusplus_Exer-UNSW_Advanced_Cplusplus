cmake_minimum_required(VERSION 3.5)
project(ass2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES EuclideanVector.cpp EuclideanVector.h)
add_executable(ass2 ${SOURCE_FILES})
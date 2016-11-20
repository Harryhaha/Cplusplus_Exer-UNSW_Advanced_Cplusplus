cmake_minimum_required(VERSION 3.6)
project(comp6771_ass4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp)
add_executable(comp6771_ass4 ${SOURCE_FILES})
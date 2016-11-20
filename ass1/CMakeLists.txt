cmake_minimum_required(VERSION 3.5)
project(ass1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -O2")

set(SOURCE_FILES WordLadder.cpp lexicon.cpp strutils.cpp genlib.cpp)
add_executable(ass1 ${SOURCE_FILES})
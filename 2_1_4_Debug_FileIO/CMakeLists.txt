cmake_minimum_required(VERSION 3.3)
project(2_1_3_Debug_FileIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(2_1_3_Debug_FileIO ${SOURCE_FILES})
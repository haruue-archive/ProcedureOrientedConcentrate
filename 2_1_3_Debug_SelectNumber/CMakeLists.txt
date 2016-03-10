cmake_minimum_required(VERSION 3.3)
project(2_1_2_Debug_SelectNumber)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(2_1_2_Debug_SelectNumber ${SOURCE_FILES})
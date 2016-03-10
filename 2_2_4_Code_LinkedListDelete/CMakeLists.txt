cmake_minimum_required(VERSION 3.3)
project(2_2_4_Code_LinkedListDelete)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp stuList.cpp stuList.h)
add_executable(2_2_4_Code_LinkedListDelete ${SOURCE_FILES})
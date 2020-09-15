cmake_minimum_required(VERSION 3.14)
project(ConcurrentMap)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ConcurrentMap main.cpp profile.h)
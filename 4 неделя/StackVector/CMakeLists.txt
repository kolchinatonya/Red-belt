cmake_minimum_required(VERSION 3.14)
project(StackVector)

set(CMAKE_CXX_STANDARD 17)

add_executable(StackVector stack_vector.cpp stack_vector.h test_runner.h profile.h)
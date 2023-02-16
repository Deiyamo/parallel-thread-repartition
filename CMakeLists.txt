cmake_minimum_required(VERSION 3.24)
project(thread_repartition)

set(CMAKE_CXX_STANDARD 17)

add_executable(thread_repartition OmpTrace.cpp)

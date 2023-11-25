cmake_minimum_required(VERSION 3.9)
project(ringbuffer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_library(ringbuffer src/ringbuffer.cpp)
target_include_directories(ringbuffer PUBLIC src/)
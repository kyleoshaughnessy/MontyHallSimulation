cmake_minimum_required(VERSION 3.6)
project(monty)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
    src/main.cpp)

add_executable(monty ${SOURCE_FILES})

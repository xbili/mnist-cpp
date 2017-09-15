cmake_minimum_required(VERSION 3.8)
project(mnist_cpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(mnist_cpp ${SOURCE_FILES})
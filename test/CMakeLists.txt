cmake_minimum_required(VERSION 3.3)

project(mnist_cpp_test)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(TEST_FILES gtest.cpp NeuronTests.cpp LayerTests.cpp)

include_directories(/usr/local/include)
add_executable(mnist_cpp_test ${TEST_FILES})

target_link_libraries(mnist_cpp_test gtest mnist_cpp_lib)
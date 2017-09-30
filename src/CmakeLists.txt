cmake_minimum_required(VERSION 3.3)

project(mnist_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(SOURCE_FILES main.cpp Neuron.cpp Neuron.h Layer.cpp Layer.h NeuralNetwork.cpp NeuralNetwork.h ../lib/csv.h DataReader.cpp DataReader.h OneHotEncoder.cpp OneHotEncoder.h Normalizer.cpp Normalizer.h OutputLayer.cpp OutputLayer.h InputLayer.cpp InputLayer.h)

add_library(mnist_cpp_lib ${SOURCE_FILES})
add_executable(mnist_cpp ${SOURCE_FILES})

target_link_libraries(mnist_cpp mnist_cpp_lib)

cmake_minimum_required(VERSION 3.8)
project(mnist_cpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Neuron.cpp src/Neuron.h src/Layer.cpp src/Layer.h src/NeuralNetwork.cpp src/NeuralNetwork.h)
add_executable(mnist_cpp ${SOURCE_FILES})
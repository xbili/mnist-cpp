cmake_minimum_required(VERSION 3.8)
project(mnist_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES src/main.cpp src/Neuron.cpp src/Neuron.h src/Layer.cpp src/Layer.h src/NeuralNetwork.cpp src/NeuralNetwork.h lib/csv.h src/DataReader.cpp src/DataReader.h src/OneHotEncoder.cpp src/OneHotEncoder.h src/Normalizer.cpp src/Normalizer.h src/OutputLayer.cpp src/OutputLayer.h src/InputLayer.cpp src/InputLayer.h)
add_executable(mnist_cpp ${SOURCE_FILES})
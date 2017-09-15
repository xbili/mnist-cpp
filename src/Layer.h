//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_LAYER_H
#define MNIST_CPP_LAYER_H


#include "Neuron.h"

class Layer {

private:
    Neuron **neurons; // Array of neurons
    int neuronCount; // The total count of neurons
    float *layerInput; // The layer inputs
    int inputCount; // The total count of elements in layer input

public:
    // Constructors & Destructors
    Layer();

    virtual ~Layer();

    // Creates the layer and initializes memory
    void create(int inputSize, int _neuronCount);

    // Calculates all neurons performing the network formula
    void calculate();
};


#endif //MNIST_CPP_LAYER_H

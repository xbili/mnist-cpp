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
    float *layerInputs; // The layer inputs
    int inputCount; // The total count of elements in layer input

public:
    // Constructors & Destructors
    Layer(int inputSize, int _neuronCount);
    virtual ~Layer();

    // Calculates all neurons performing the network formula
    void calculate();

    // Getters
    Neuron **getNeurons() const;
    Neuron *getNeuron(int i) const;
    int getNeuronCount() const;
    float getLayerInput(int i) const;
    float *getLayerInputs() const;
    int getInputCount() const;

    // Setters
    void setLayerInput(int i, float layerInput);
};


#endif //MNIST_CPP_LAYER_H

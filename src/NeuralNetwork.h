//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_NEURALNETWORK_H
#define MNIST_CPP_NEURALNETWORK_H


#include "Layer.h"

class NeuralNetwork {
private:
    Layer *m_inputLayer; // Input layer of the network
    Layer *m_outputLayer; // Output layer - contains the result of applying the network on a set of inputs
    Layer **m_hiddenLayers; // Additional hidden layers
    int m_hiddenLayerCount; // Number of additional hidden layers

public:
    // Constructors & Destructors
    NeuralNetwork(
            int inputCount,
            int inputNeurons,
            int outputCount,
            int *hiddenLayers,
            int hiddenLayerCount
    );
    virtual ~NeuralNetwork();

    // Updates the weight values of the network given a desired output and applying the backpropagation algorithm
    float train(const float *desiredOutput, const float *input, float alpha, float momentum);

    // Updates the next layer input values
    void update(int layerIndex);

    void propagate(const float *input);

    // Returns the output layer
    inline Layer* getOutput() {
        return m_outputLayer;
    }
};


#endif //MNIST_CPP_NEURALNETWORK_H

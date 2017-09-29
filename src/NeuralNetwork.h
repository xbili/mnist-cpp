//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_NEURALNETWORK_H
#define MNIST_CPP_NEURALNETWORK_H


#include "Layer.h"
#include "OutputLayer.h"

class NeuralNetwork {
private:
    Layer m_inputLayer; // Input layer of the network
    OutputLayer m_outputLayer; // Output layer - contains the result of applying the network on a set of inputs
    vector<Layer> m_hiddenLayers; // Additional hidden layers
    int m_hiddenLayerCount; // Number of additional hidden layers

public:
    // Constructors & Destructors
    NeuralNetwork(
            int inputCount,
            int inputNeurons,
            int outputCount,
            vector<int> hiddenLayers,
            int hiddenLayerCount
    );
    virtual ~NeuralNetwork();

    void update(int layerIndex);
    void propagate(vector<float> input const);
    void setHiddenLayerWeights(int i, vector<vector<float>> weights const, vector<float> biasWeights const);
    void setOutputLayerWeights(vector<vector<float>> weights const, vector<float> biasWeights const);

    // Returns the output layer
    inline Layer getOutput() {
        return m_outputLayer;
    }
};


#endif //MNIST_CPP_NEURALNETWORK_H

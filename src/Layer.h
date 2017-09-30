//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_LAYER_H
#define MNIST_CPP_LAYER_H


#include <vector>
#include "Neuron.h"

using namespace std;

class Layer {

protected:
    vector<Neuron*> neurons; // Matrix of neurons
    vector<float> inputs; // The layer inputs

public:
    // Constructors & Destructors
    Layer(int inputSize, int neuronCount);
    virtual ~Layer();

    // Calculates all neurons performing the network formula
    void calculate();

    // Getters
    const vector<Neuron*> &getNeurons() const;
    const vector<float> &getInputs() const;
    Neuron* getNeuron(int i);
    int getNeuronCount() const;
    int getInputCount() const;

    // Setters
    void setLayerInput(int i, float layerInput);
    void setWeights(vector<vector<float>> weights);
    void setBiasWeights(vector<float> biasWeights);
};


#endif //MNIST_CPP_LAYER_H

//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_LAYER_H
#define MNIST_CPP_LAYER_H


#include <vector>
#include "Neuron.h"

using namespace std;

class Layer {

private:
    vector<Neuron> neurons; // Matrix of neurons
    vector<float> inputs; // The layer inputs

public:
    // Constructors & Destructors
    Layer(int inputSize, int neuronCount);
    virtual ~Layer();

    // Calculates all neurons performing the network formula
    void calculate();

    // Getters
    const vector<Neuron> &getNeurons() const;
    const vector<float> &getInputs() const;
    int getNeuronCount() const;
    int getInputCount() const;

    // Setters
    void setLayerInput(int i, float layerInput);
    void setWeights(float **weights);
    void setBiasWeights(float *biasWeights);
};


#endif //MNIST_CPP_LAYER_H

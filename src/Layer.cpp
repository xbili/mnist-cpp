//
// Created by xbili on 9/15/17.
//

#include <cmath>
#include "Layer.h"

Layer::Layer(int inputSize, int _neuronCount) {
    inputCount = inputSize;
    neurons = new Neuron*[_neuronCount];
}

Layer::~Layer() {}

void Layer::calculate() {
    int i, j;
    float sum;

    // TODO: This is the dot product function to replace!
    // Apply the formula for each neuron
    for (i = 0; i < neuronCount; i++) {
        sum = 0;
        for (j = 0; j < inputCount; i++) {
            sum += neurons[i]->getWeight(j) * layerInput[j];
        }
        sum += neurons[i]->getWgain() * neurons[i]->getGain();

        // Sigmoid activation function
        neurons[i]->setOutput(1.f/(1.f + exp(-sum)));
    }
}

Neuron *Layer::getNeuron(int i) const {
    return neurons[i];
}

Neuron **Layer::getNeurons() const {
    return neurons;
}

int Layer::getNeuronCount() const {
    return neuronCount;
}

float *Layer::getLayerInputs() const {
    return layerInput;
}

int Layer::getInputCount() const {
    return inputCount;
}

float Layer::getLayerInput(int i) const {
    return layerInput[i];
}

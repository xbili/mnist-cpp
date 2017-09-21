//
// Created by xbili on 9/15/17.
//

#include <math.h>
#include <assert.h>
#include "Layer.h"

Layer::Layer(int inputSize, int _neuronCount) {
    assert(inputSize && _neuronCount);

    // Create neurons in this layer
    neurons = new Neuron*[_neuronCount];
    for (int i = 0; i < _neuronCount; i++) {
        neurons[i] = new Neuron(inputSize);
    }

    layerInputs = new float[inputSize];
    neuronCount = _neuronCount;
    inputCount = inputSize;
}

Layer::~Layer() {}

void Layer::calculate() {
    float sum;

    // TODO: This is the dot product function to replace!
    // Apply the formula for each neuron
    for (int i = 0; i < neuronCount; i++) {
        sum = 0;
        for (int j = 0; j < inputCount; j++) {
            sum += neurons[i]->getWeight(j) * layerInputs[j];
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
    return layerInputs;
}

int Layer::getInputCount() const {
    return inputCount;
}

float Layer::getLayerInput(int i) const {
    return layerInputs[i];
}

void Layer::setLayerInput(int i, float layerInput) {
    layerInputs[i] = layerInput;
}

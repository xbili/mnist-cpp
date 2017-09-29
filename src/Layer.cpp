//
// Created by xbili on 9/15/17.
//

#include <math.h>
#include <assert.h>
#include <algorithm>
#include "Layer.h"

Layer::Layer(int inputSize, int _neuronCount) {
    assert(inputSize && _neuronCount);

    // Create neurons in this layer
    neurons = new Neuron*[_neuronCount + 1]; // +1 for bias
    for (int i = 0; i < _neuronCount; i++) {
        neurons[i] = new Neuron(inputSize);
    }

    // Create a bias neuron
    neurons[_neuronCount] = new Neuron(inputSize);
    neurons[_neuronCount]->setOutput(1.0);

    layerInputs = new float[inputSize];
    neuronCount = _neuronCount;
    inputCount = inputSize;
}

Layer::~Layer() {}

void Layer::calculate() {
    float sum;

    // Apply the formula for each neuron
    for (int i = 0; i < neuronCount; i++) { // +1 for bias neuron
        // TODO: This is the dot product function to replace!
        sum = 0;
        for (int j = 0; j < inputCount; j++) {
            sum += neurons[i]->getWeight(j) * layerInputs[j];
        }

        // ReLU activation function
        if (sum > 0) {
            neurons[i]->setOutput(sum);
        } else {
            neurons[i]->setOutput(0);
        }
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

void Layer::setWeights(float **weights) {
    for (int i = 0; i < neuronCount; i++) {
        neurons[i]->setWeights(weights[i]);
    }
}

void Layer::setBiasWeights(float *biasWeights) {
    neurons[neuronCount]->setWeights(biasWeights);
}

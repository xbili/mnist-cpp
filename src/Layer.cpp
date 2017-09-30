//
// Created by xbili on 9/15/17.
//

#include <math.h>
#include <algorithm>
#include "Layer.h"

Layer::Layer(int inputSize, int neuronCount) {
    // Initialize vector of neurons
    for (int i = 0; i < neuronCount + 1; i++) {
        neurons.push_back(new Neuron(inputSize));
    }

    // Bias neuron output is always 1.0
    neurons.back()->setOutput(1.0);

    // Initialize vector of inputs
    for (int i = 0; i < inputSize; i++) {
        inputs.push_back(0);
    }
}

Layer::~Layer() {
    // Delete data allocated for neurons
    for (int i = 0; i < neurons.size(); i++) {
        delete(neurons[i]);
    }
}

void Layer::calculate() {
    float sum;

    // Apply the formula for each neuron
    for (int i = 0; i < neurons.size(); i++) { // +1 for bias neuron
        // TODO: This is the dot product function to replace!
        sum = 0;
        for (int j = 0; j < neurons.size(); j++) {
            sum += neurons[i]->getWeight(j) * inputs[j];
        }

        // ReLU activation function
        if (sum > 0) {
            neurons[i]->setOutput(sum);
        } else {
            neurons[i]->setOutput(0);
        }
    }
}

int Layer::getNeuronCount() const {
    return neurons.size();
}

int Layer::getInputCount() const {
    return inputs.size();
}

const vector<Neuron*> &Layer::getNeurons() const {
    return neurons;
}

const vector<float> &Layer::getInputs() const {
    return inputs;
}

void Layer::setLayerInput(int i, float layerInput) {
    inputs[i] = layerInput;
}

void Layer::setWeights(vector<vector<float>> weights) {
    for (int i = 0; i < neurons.size() - 1; i++) { // -1 to account for bias
        neurons[i]->setWeights(weights[i]);
    }
}

void Layer::setBiasWeights(vector<float> biasWeights) {
    neurons.back()->setWeights(biasWeights);
}

Neuron* Layer::getNeuron(int i) {
    return neurons[i];
}

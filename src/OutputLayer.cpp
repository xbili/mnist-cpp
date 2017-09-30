//
// Created by xbili on 9/29/17.
//

#include <math.h>
#include "OutputLayer.h"

OutputLayer::OutputLayer(int inputSize, int _neuronCount) : Layer(inputSize, _neuronCount) {
}

void OutputLayer::calculate() {
    // Still calculate the original output values
    float sum;
    for (int i = 0; i < neurons.size() - 1; i++) {
        // TODO: This is the dot product function to replace!
        sum = 0;
        for (int j = 0; j < getInputCount(); j++) {
            sum += neurons[i]->getWeight(j) * inputs[j];
        }
        neurons[i]->setOutput(sum);
    }

    // Set the output value for our bias neuron
    sum = 0;
    for (int i = 0; i < getInputCount(); i++) {
        sum += neurons.back()->getWeight(i) * 1.0;
    }
    neurons.back()->setOutput(sum);

    // Softmax - squash it!
    float total = 0;
    for (int i = 0; i < neurons.size(); i++) {
        total += exp(neurons[i]->getOutput());
    }

    for (int i = 0; i < neurons.size(); i++) {
        float originalOutput = neurons[i]->getOutput();
        neurons[i]->setOutput(exp(originalOutput) / total);
    }
}

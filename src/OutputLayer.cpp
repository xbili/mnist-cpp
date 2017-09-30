//
// Created by xbili on 9/29/17.
//

#include <math.h>
#include "OutputLayer.h"

OutputLayer::OutputLayer(int inputSize, int _neuronCount) : Layer(inputSize, _neuronCount) {
}

void OutputLayer::calculate() {
    // Still calculate the original output values
    Layer::calculate();

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

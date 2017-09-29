//
// Created by xbili on 9/29/17.
//

#include <math.h>
#include "OutputLayer.h"

OutputLayer::OutputLayer(int inputSize, int _neuronCount) : Layer(inputSize, _neuronCount) {}

void OutputLayer::calculate() {
    // Still calculate the original output values
    Layer::calculate();

    // Softmax - squash it!
    float total = 0;
    for (int i = 0; i < getNeuronCount(); i++) {
        total += exp(getNeuron(i)->getOutput());
    }

    for (int i = 0; i < getNeuronCount(); i++) {
        float originalOutput = getNeuron(i)->getOutput();
        getNeuron(i)->setOutput(exp(originalOutput) / total);
    }
}

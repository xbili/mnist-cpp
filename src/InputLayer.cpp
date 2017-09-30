//
// Created by xbili on 9/30/17.
//

#include "InputLayer.h"

void InputLayer::calculate() {
    // Run every input through the ReLU activation function and set it as the neuron output
    vector<float> inputs = getInputs();
    for (int i = 0; i < getInputCount(); i++) {
        if (inputs[i] < 0) {
            getNeuron(i)->setOutput(0);
        } else {
            getNeuron(i)->setOutput(inputs[i]);
        }
    }
}

InputLayer::InputLayer(int inputSize, int _neuronCount) : Layer(inputSize, _neuronCount) {
}

//
// Created by xbili on 9/15/17.
//
#include <iostream>
#include <assert.h>
#include "Neuron.h"

Neuron::Neuron(int inputCount) {
    assert(inputCount);

    float sign = -1;
    float random;

    random = (float(rand()) / float(RAND_MAX)) / 2.f;
    random *= sign;
    sign *= -1;

    gain = 1;
    wgain = random;

    // Initialize all weights as random assigned values
    for (int i = 0; i < inputCount; i++) {
        // Get a random number between -0.5 to 0.5
        random = (float(rand()) / float(RAND_MAX)) / 2.f; // min 0.5;
        random *= sign;
        sign *= -1;

        weights.push_back(random);
        deltaValues.push_back(0);
    }
}

Neuron::~Neuron() {}

float Neuron::getWeight(int i) const {
    return weights[i];
}

float Neuron::getWgain() const {
    return wgain;
}

float Neuron::getOutput() const {
    return output;
}

float Neuron::getGain() const {
    return gain;
}

void Neuron::setWeight(int i, float weight) {
    weights[i] = weight;
}

void Neuron::setOutput(float output) {
    Neuron::output = output;
}

float Neuron::getDeltaValue(int i) const {
    return deltaValues[i];
}

void Neuron::setDeltaValue(int i, float delta) {
    deltaValues[i] = delta;
}

void Neuron::incrementWgain(float value) {
    wgain += value;
}

void Neuron::setWeights(const vector<float> &weights) {
    Neuron::weights = weights;
}

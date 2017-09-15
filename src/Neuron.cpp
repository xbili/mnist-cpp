//
// Created by xbili on 9/15/17.
//

#include "Neuron.h"

Neuron::Neuron(int inputCount) {
    weights = new float[inputCount];
    deltaValues = new float[inputCount];
}

Neuron::~Neuron() {}

float Neuron::getWeight(int i) const {
    return weights[i];
}

float *Neuron::getWeights() const {
    return weights;
}

float Neuron::getWgain() const {
    return wgain;
}

float *Neuron::getDeltaValues() const {
    return deltaValues;
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

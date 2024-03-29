//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_NEURON_H
#define MNIST_CPP_NEURON_H


#include <vector>

using namespace std;

class Neuron {

private:
    vector<float> weights;
public:
    const vector<float> &getWeights() const;

private:
    // Neuron input weights
    vector<float> deltaValues; // Neuron delta values
    float output = 0; // Output value
    float gain = 0; // Gain value
    float wgain = 0;

public:
    // Constructors & Destructors
    Neuron(int inputCount);
    virtual ~Neuron();

    float getWeight(int i) const;
    float getDeltaValue(int i) const;
    float getOutput() const;
    float getGain() const;
    float getWgain() const;

    void setOutput(float output);
    void setWeight(int i, float weight);
    void setWeights(const vector<float> weights);
    void setDeltaValue(int i, float delta);
    void incrementWgain(float wgain);
};


#endif //MNIST_CPP_NEURON_H

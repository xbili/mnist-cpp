//
// Created by xbili on 9/15/17.
//

#ifndef MNIST_CPP_NEURON_H
#define MNIST_CPP_NEURON_H


class Neuron {

private:
    float *weights; // Neuron input weights
    float *deltaValues; // Neuron delta values
    float output; // Output value
    float gain; // Gain value
    float wgain;

public:
    // Constructors & Destructors
    Neuron(int inputCount);
    virtual ~Neuron();

    float getWeight(int i) const;
    float *getWeights() const;
    float getDeltaValue(int i) const;
    float *getDeltaValues() const;
    float getOutput() const;
    float getGain() const;
    float getWgain() const;

    void setOutput(float output);
    void setWeight(int i, float weight);
    void setDeltaValue(int i, float delta);
    void incrementWgain(float wgain);
};


#endif //MNIST_CPP_NEURON_H

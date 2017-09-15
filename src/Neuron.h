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
    float wgain; // Weight gain value

public:
    // Constructors & Destructors
    Neuron();
    virtual ~Neuron();

     // Allocates memory and intitializes values
    void create(int inputCount);
};


#endif //MNIST_CPP_NEURON_H

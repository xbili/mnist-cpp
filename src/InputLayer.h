//
// Created by xbili on 9/30/17.
//

#ifndef MNIST_CPP_INPUTLAYER_H
#define MNIST_CPP_INPUTLAYER_H


#include "Layer.h"

class InputLayer : public Layer {
public:
    InputLayer(int inputSize, int _neuronCount);

    void calculate();
};


#endif //MNIST_CPP_INPUTLAYER_H

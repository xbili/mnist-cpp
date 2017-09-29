//
// Created by xbili on 9/29/17.
//

#ifndef MNIST_CPP_OUTPUTLAYER_H
#define MNIST_CPP_OUTPUTLAYER_H


#include "Layer.h"

class OutputLayer : public Layer {
public:
    OutputLayer(int inputSize, int _neuronCount);

    void calculate();

};


#endif //MNIST_CPP_OUTPUTLAYER_H

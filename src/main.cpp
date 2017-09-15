#include <iostream>
#include "NeuralNetwork.h"

#define PATTERN_COUNT 4
#define PATTERN_SIZE 2
#define NETWORK_INPUTNEURONS 2
#define NETWORK_OUTPUT 1
#define HIDDEN_LAYERS 0
#define EPOCHS 1000000

int main() {
    // XOR input values
    float pattern[PATTERN_COUNT][PATTERN_SIZE] = {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    //XOR expected output values
    float expected[PATTERN_COUNT][NETWORK_OUTPUT] = {
        {0},
        {1},
        {1},
        {0}
    };

    int hiddenLayers[1] = { 5 };
    NeuralNetwork* net = new NeuralNetwork(PATTERN_SIZE, NETWORK_INPUTNEURONS,
                                           NETWORK_OUTPUT, hiddenLayers, HIDDEN_LAYERS);

    // Start training the neural network
    float error;
    for (int i = 0; i < EPOCHS; i++) {
        error = 0;
        for (int j = 0; j < PATTERN_COUNT; j++) {
            error += net->train(expected[j], pattern[j], 0.2f, 0.1f);
        }
        error /= PATTERN_COUNT;

        if (i % 10000 == 0) {
            std::cout << "Epoch: " << i << " ERROR:" << error << "\r" << std::endl;
        }
    }

    // After training...let's predict!
    for (int i = 0; i < PATTERN_COUNT; i++) {
        net->propagate(pattern[i]);
        std::cout << "TESTED PATTERN " << i << " DESIRED OUTPUT: " << *expected[i] << " NET RESULT: "<< net->getOutput()->getNeuron(0)->getOutput() << std::endl;
    }

    return 0;
}
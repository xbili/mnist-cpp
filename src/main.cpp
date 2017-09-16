#include <iostream>
#include <iomanip>
#include "NeuralNetwork.h"
#include "../lib/csv.h" // Figure out how to import cleanly, this is messy AF
#include "DataReader.h"

#define TRAIN_PATTERN_COUNT 60000
#define TEST_PATTERN_COUNT 60000
#define PATTERN_SIZE 784
#define NETWORK_INPUTNEURONS 784
#define NETWORK_OUTPUT 10
#define HIDDEN_LAYERS 0
#define EPOCHS 20000

void printImage(float expected, float* input);

int main() {
    // Read data in from CSV
    DataReader* trainReader = new DataReader("../data/train.csv", PATTERN_SIZE + 1, 0, TRAIN_PATTERN_COUNT);
    DataReader* testReader = new DataReader("../data/test.csv", PATTERN_SIZE + 1, 0, TEST_PATTERN_COUNT);

    NeuralNetwork* net = new NeuralNetwork(PATTERN_SIZE, NETWORK_INPUTNEURONS,
                                           NETWORK_OUTPUT, HIDDEN_LAYERS, HIDDEN_LAYERS);

    float** trainX = trainReader->getInputs();
    float** trainY = trainReader->getLabels();


    // Start training the neural network
    /*
    float error;
    for (int i = 0; i < EPOCHS; i++) {
        error = 0;
        for (int j = 0; j < TRAIN_PATTERN_COUNT; j++) {
            error += net->train(expected[j], pattern[j], 0.2f, 0.1f);
        }
        error /= TRAIN_PATTERN_COUNT;

        if (i % 10000 == 0) {
            std::cout << "Epoch: " << i << " ERROR:" << error << "\r" << std::endl;
        }
    }

    // After training...let's predict!
    for (int i = 0; i < TEST_PATTERN_COUNT; i++) {
        net->propagate(pattern[i]);
        std::cout << "TESTED PATTERN " << i << " DESIRED OUTPUT: " << *expected[i] << " NET RESULT: "<< net->getOutput()->getNeuron(0)->getOutput() << std::endl;
    }
     */

    return 0;
}

void printImage(float expected, float* input) {
     for (int i = 0; i < TRAIN_PATTERN_COUNT; i++) {
        std::cout << "===============================" << std::endl;
        std::cout << "Expected:" << expected << std::endl;
        std::cout << "===============================" << std::endl;

        for (int j = 0; j < 28; j++) {
            for (int k = 0; k < 28; k++) {
                float value = input[j*28 + k];
                if (value != 0) {
                    printf("x");
                } else {
                    printf(" ");
                }
            }
            std::cout << std::endl;
        }

        std::cout << "===============================" << std::endl;
    }
}
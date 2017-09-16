#include <iostream>
#include <iomanip>
#include "NeuralNetwork.h"
#include "../lib/csv.h" // Figure out how to import cleanly, this is messy AF
#include "DataReader.h"
#include "OneHotEncoder.h"

#define TRAIN_PATTERN_COUNT 60000
#define TEST_PATTERN_COUNT 60000
#define PATTERN_SIZE 784
#define NETWORK_INPUTNEURONS 784
#define NETWORK_OUTPUT 10
#define HIDDEN_LAYERS 0
#define EPOCHS 2000

void printImage(float expected, float* input);

int main() {

    std::cout << "Loading training data..." << std::endl;

    // Read data in from CSV
    DataReader* trainReader = new DataReader("../data/train.csv", PATTERN_SIZE + 1, 0, TRAIN_PATTERN_COUNT);

    float** trainX = trainReader->getInputs();
    float* trainY = trainReader->getLabels();

    std::cout << "Data loading complete." << std::endl;

    std::cout << "Encoding data..." << std::endl;

    OneHotEncoder* encoder = new OneHotEncoder(trainY, 10, TRAIN_PATTERN_COUNT);
    float** encodedY = encoder->getEncoded();

    std::cout << "Encoding data complete." << std::endl;

    std::cout << "Training neural network..." << std::endl;

    // Create the neural network
    NeuralNetwork* net = new NeuralNetwork(PATTERN_SIZE, NETWORK_INPUTNEURONS,
                                           NETWORK_OUTPUT, HIDDEN_LAYERS, HIDDEN_LAYERS);

    // Start training the neural network
    float error;
    for (int i = 0; i < EPOCHS; i++) {
        error = 0;
        for (int j = 0; j < TRAIN_PATTERN_COUNT; j++) {
            error += net->train(trainX[j], encodedY[j], 0.2f, 0.1f);
        }
        error /= TRAIN_PATTERN_COUNT;
        std::cout << "Epoch: " << i << " ERROR:" << error << "\r" << std::endl;
    }

    std::cout << "Training complete..." << std::endl;

    std::cout << "Loading test data..." << std::endl;

    DataReader* testReader = new DataReader("../data/test.csv", PATTERN_SIZE + 1, 0, TEST_PATTERN_COUNT);

    float** testX = trainReader->getInputs();
    float* testY = trainReader->getLabels();

    std::cout << "Data loading complete." << std::endl;

    std::cout << "Encoding data..." << std::endl;

    OneHotEncoder* testEncoder = new OneHotEncoder(testY, 10, TRAIN_PATTERN_COUNT);
    float** encodedTestY = testEncoder->getEncoded();

    std::cout << "Encoding data complete." << std::endl;

    std::cout << "Starting prediction..." << std::endl;

    // After training...let's predict!
    for (int i = 0; i < TEST_PATTERN_COUNT; i++) {
        net->propagate(testX[i]);
        std::cout << "TESTED PATTERN " << i << " DESIRED OUTPUT: " << testY[i] << std::endl;
        Neuron **outputNeurons = net->getOutput()->getNeurons();
        for (int j = 0; j < 10; j++) {
            std::cout << "P(Y = " << j << "):" << outputNeurons[j]->getOutput() << std::endl;
        }
    }

    std::cout << "Prediction complete!" << std::endl;

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
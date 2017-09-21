#include <iostream>
#include <iomanip>
#include <cmath>
#include "NeuralNetwork.h"
#include "../lib/csv.h" // Figure out how to import cleanly, this is messy AF
#include "DataReader.h"
#include "OneHotEncoder.h"

#define TRAIN_PATTERN_COUNT 60000
#define TEST_PATTERN_COUNT 10000
#define PATTERN_SIZE 784
#define NETWORK_INPUTNEURONS 784
#define NETWORK_OUTPUT 10
#define HIDDEN_LAYERS 1
#define EPOCHS 1

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
    int hiddenLayers[1] = { 16 };
    NeuralNetwork* net = new NeuralNetwork(PATTERN_SIZE, NETWORK_INPUTNEURONS,
                                           NETWORK_OUTPUT, hiddenLayers, HIDDEN_LAYERS);

    // Start training the neural network
    float error;
    for (int i = 0; i < EPOCHS; i++) {
        error = 0;
        for (int j = 0; j < TRAIN_PATTERN_COUNT; j++) {
            error += net->train(trainX[j], encodedY[j], 0.2f, 0.1f);
        }
        error /= TRAIN_PATTERN_COUNT;
        std::cout << "Epoch #" << i << " ERROR:" << error << "\r" << std::endl;
    }

    std::cout << "Training complete..." << std::endl;

    std::cout << "Loading test data..." << std::endl;

    DataReader* testReader = new DataReader("../data/test.csv", PATTERN_SIZE + 1, 0, TEST_PATTERN_COUNT);
    float** testX = testReader->getInputs();
    float* testY = testReader->getLabels();

    std::cout << "Data loading complete." << std::endl;

    std::cout << "Starting prediction..." << std::endl;

    int correctPredictions = 0;

    // After training...let's predict!
    for (int i = 0; i < TEST_PATTERN_COUNT; i++) {
        net->propagate(testX[i]);

        std::cout << "TESTED PATTERN " << i << " DESIRED OUTPUT: " << testY[i] << std::endl;
        Layer *outputLayer = net->getOutput();

        float sum = 0;
        for (int j = 0; j < 10; j++) {
            sum += exp(outputLayer->getNeuron(j)->getOutput());
        }

        float probs[10];
        for (int j = 0; j < 10; j++) {
            probs[j] = (float) exp(outputLayer->getNeuron(j)->getOutput()) / sum;
        }

        int prediction = (int) std::distance(probs, std::max_element(probs, probs + 10));

        if (prediction == testY[i]) {
            correctPredictions++;
        }

        std::cout << "Prediction: " << prediction << std::endl;
        std::cout << "===================================" << std::endl;
    }

    std::cout << "Prediction complete!" << std::endl;
    std::cout << "Correct Predictions: " << correctPredictions << std::endl;

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

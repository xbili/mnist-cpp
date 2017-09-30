#include <iostream>
#include <iomanip>
#include <cmath>
#include "NeuralNetwork.h"
#include "../lib/csv.h" // Figure out how to import cleanly, this is messy AF
#include "DataReader.h"
#include "OneHotEncoder.h"
#include "Normalizer.h"

#define TRAIN_PATTERN_COUNT 60000
#define TEST_PATTERN_COUNT 10000
#define PATTERN_SIZE 784
#define NETWORK_INPUT_NEURONS 784
#define NETWORK_OUTPUT 10

void printImage(float expected, float* input);
vector<vector<float>> readLayerWeights(string filename);
vector<float> readBiasWeights(string filename);

int main() {

    // Read data in from CSV
    std::cout << "Loading training data..." << std::endl;

    // Train
    DataReader* trainReader = new DataReader("../data/train.csv", PATTERN_SIZE + 1, 0, TRAIN_PATTERN_COUNT);
    float** trainX = trainReader->getInputs();
    float* trainY = trainReader->getLabels();

    // Test
    DataReader* testReader = new DataReader("../data/test.csv", PATTERN_SIZE + 1, 0, TEST_PATTERN_COUNT);
    float** testX = testReader->getInputs();
    float* testY = testReader->getLabels();

    std::cout << "Data loading complete." << std::endl;


    /************************
     * Normalize input data *
     ************************/
    std::cout << "Normalizing data..." << std::endl;

    // Train
    Normalizer* normalizer = new Normalizer(trainX);
    vector<vector<float>> normalizedTrainX = normalizer->getNormalized();

    // Test
    Normalizer* testNormalizer = new Normalizer(testX);
    vector<vector<float>> normalizedTestX = testNormalizer->getNormalized();

    std::cout << "Normalizing data complete." << std::endl;


    /*************************
     * One-hot encode labels *
     *************************/

    std::cout << "Encoding data..." << std::endl;

    // Train
    OneHotEncoder* trainEncoder = new OneHotEncoder(trainY, 10, TRAIN_PATTERN_COUNT);
    float** encodedTrainY = trainEncoder->getEncoded();

    // Test
    OneHotEncoder* testEncoder = new OneHotEncoder(testY, 10, TEST_PATTERN_COUNT);
    float** encodedTestY = testEncoder->getEncoded();

    std::cout << "Encoding data complete." << std::endl;

    /**
     * Load pre-trained weights from Keras.
     */
    vector<int> hiddenLayers = { 512 };
    NeuralNetwork* net = new NeuralNetwork(
            PATTERN_SIZE,
            NETWORK_INPUT_NEURONS,
            NETWORK_OUTPUT,
            hiddenLayers
    );

    // Read in the weights
    vector<vector<float>> layer1Weights = readLayerWeights("../data/hidden_layer_weights.csv");
    vector<vector<float>> outputLayerWeights = readLayerWeights("../data/output_layer_weights.csv");

    vector<float> layer1BiasWeights = readBiasWeights("../data/hidden_layer_bias_weights.csv");
    vector<float> outputLayerBiasWeights = readBiasWeights("../data/output_layer_bias_weights.csv");

    net->setHiddenLayerWeights(0, layer1Weights, layer1BiasWeights);
    net->setOutputLayerWeights(outputLayerWeights, outputLayerBiasWeights);

    std::cout << "Starting prediction..." << std::endl;

    int correctPredictions = 0;

    // After training...let's predict!
    for (int i = 0; i < TEST_PATTERN_COUNT; i++) {
        net->propagate(normalizedTestX[i]);

        // std::cout << "TESTED PATTERN " << i << " DESIRED OUTPUT: " << testY[i] << std::endl;
        Layer *outputLayer = net->getOutput();

        int prediction;
        float maxProb = 0;
        for (int j = 0; j < 10; j++) {
            float curr = outputLayer->getNeuron(j)->getOutput();
            if (curr > maxProb) {
                maxProb = curr;
                prediction = j;
            }
        }

        if (prediction == testY[i]) {
            correctPredictions++;
        }

        /*
        std::cout << "Prediction: " << prediction << std::endl;
        std::cout << "===================================" << std::endl;
         */
    }

    std::cout << "Prediction complete!" << std::endl;
    std::cout << "Correct Predictions: " << correctPredictions << std::endl;

    return 0;
}

void printImage(float expected, float* input) {
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

vector<vector<float>> readLayerWeights(string filename) {
    vector<vector<float>> results;
    io::LineReader* reader = new io::LineReader(filename);
    int rowNum = 0;
    while (char* line = reader->next_line()) {
        vector<float> weights;
        vector<char*> row;

        row.push_back(line);

        while (*line != '\0') {
            if (*line == ',') {
                *line = '\0';
                row.push_back(line+1);
            }
            line++;
        }

        for (int i = 0; i < row.size(); i++) {
            weights.push_back(strtof(row.at(i), NULL));
        }

        results.push_back(weights);

        rowNum++;
    }
}

vector<float> readBiasWeights(string filename) {
    vector<float> weights;

    io::LineReader* reader = new io::LineReader(filename);
    int rowNum = 0;
    while (char* line = reader->next_line()) {
        std::vector<char*> row;
        row.push_back(line);
        while (*line != '\0') {
            if (*line == ',') {
                *line = '\0';
                row.push_back(line+1);
            }
            line++;
        }

        for (int i = 0; i < row.size(); i++) {
            weights.push_back(strtof(row.at(i), NULL));
        }

        rowNum++;
    }

    return weights;
}

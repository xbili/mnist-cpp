//
// Created by xbili on 9/15/17.
//

#include <cstring>
#include "NeuralNetwork.h"
#include "OutputLayer.h"

NeuralNetwork::NeuralNetwork(
        int inputCount,
        int inputNeurons,
        int outputCount,
        int *hiddenLayers,
        int hiddenLayerCount
) {
    m_inputLayer = new Layer(inputCount, inputNeurons);

    if (hiddenLayerCount > 0) {
        m_hiddenLayers = new Layer*[hiddenLayerCount];
        m_hiddenLayerCount = hiddenLayerCount;

        // First hidden layer receives the output of the input layer
        m_hiddenLayers[0] = new Layer(inputNeurons, hiddenLayers[0]);
        for (int i = 1; i < hiddenLayerCount; i++) {
            m_hiddenLayers[i] = new Layer(hiddenLayers[i-1], hiddenLayers[i]);
        }

        m_outputLayer = new OutputLayer(hiddenLayers[hiddenLayerCount - 1], outputCount);
    } else {
        m_outputLayer = new OutputLayer(inputNeurons, outputCount);
    }
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::update(int layerIndex) {
    if (layerIndex == -1) { // Input layer update
        m_inputLayer->calculate();

        if (m_hiddenLayerCount > 0) {
            // Push input layer outputs to first hidden layer inputs
            for (int i = 0; i < m_hiddenLayers[0]->getInputCount(); i++) {
                m_hiddenLayers[0]->setLayerInput(i, m_inputLayer->getNeuron(i)->getOutput());
            }
        } else {
            // Push input layer outputs to the output layer inputs
            for (int i = 0; i < m_outputLayer->getInputCount(); i++) {
                m_outputLayer->setLayerInput(i, m_inputLayer->getNeuron(i)->getOutput());
            }
        }
    } else if (layerIndex < m_hiddenLayerCount) { // Hidden layer update
        m_hiddenLayers[layerIndex]->calculate();

        if (layerIndex + 1 >= m_hiddenLayerCount) {
            // Push outputs to the output layer inputs
            for (int i = 0; i < m_outputLayer->getInputCount(); i++) {
                m_outputLayer->setLayerInput(i, m_hiddenLayers[layerIndex]->getNeuron(i)->getOutput());
            }
        } else {
            // Push outputs to the next hidden layer inputs
            for (int i = 0; i < m_hiddenLayers[layerIndex + 1]->getInputCount(); i++) {
                m_hiddenLayers[layerIndex + 1]->setLayerInput(i, m_hiddenLayers[layerIndex]->getNeuron(i)->getOutput());
            }
        }
    } else { // Output layer update
        m_outputLayer->calculate();
    }
}

void NeuralNetwork::propagate(const float *input) {
    // Set input layer values
    for (int i = 0; i < m_inputLayer->getInputCount(); i++) {
        m_inputLayer->setLayerInput(i, input[i]);
    }

    update(-1); // Propagate the input layer first

    // Then propagate the hidden layers
    for (int i = 0; i < m_hiddenLayerCount; i++) {
        update(i);
    }

    // Last but not least, propagate the output layer (last layer)
    update(m_hiddenLayerCount);
}

void NeuralNetwork::setInputLayerWeights(float **weights, float *biasWeights) {
    m_inputLayer->setWeights(weights);
}

void NeuralNetwork::setHiddenLayerWeights(int i, float **weights, float *biasWeights) {
    m_hiddenLayers[i]->setWeights(weights);
}

void NeuralNetwork::setOutputLayerWeights(float **weights, float *biasWeights) {
    m_outputLayer->setWeights(weights);
}



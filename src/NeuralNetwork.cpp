//
// Created by xbili on 9/15/17.
//

#include <cstring>
#include "NeuralNetwork.h"
#include "InputLayer.h"

NeuralNetwork::NeuralNetwork(
        int inputCount,
        int inputNeurons,
        int outputCount,
        vector<int> hiddenLayers
) {
    m_inputLayer = new InputLayer(inputCount, inputNeurons);

    if (hiddenLayers.size() > 0) {
        // First hidden layer receives the output of the input layer
        m_hiddenLayers.push_back(new Layer(inputNeurons, hiddenLayers[0]));

        for (int i = 1; i < hiddenLayers.size(); i++) {
            m_hiddenLayers.push_back(new Layer(hiddenLayers[i-1], hiddenLayers[i]));
        }

        m_outputLayer = new OutputLayer(hiddenLayers.back(), outputCount);
    } else {
        m_outputLayer = new OutputLayer(inputNeurons, outputCount);
    }
}

NeuralNetwork::~NeuralNetwork() {
    for (int i = 0; m_hiddenLayers.size(); i++) {
        delete(m_hiddenLayers[i]);
    }

    delete(m_inputLayer);
    delete(m_outputLayer);
}

void NeuralNetwork::update(int layerIndex) {
    if (layerIndex == -1) { // Input layer update
        m_inputLayer->calculate();

        if (m_hiddenLayers.size() > 0) {
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
    } else if (layerIndex < m_hiddenLayers.size()) { // Hidden layer update
        m_hiddenLayers[layerIndex]->calculate();

        if (layerIndex + 1 >= m_hiddenLayers.size()) {
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

void NeuralNetwork::propagate(vector<float> input) {
    // Set input layer values
    for (int i = 0; i < m_inputLayer->getInputCount(); i++) {
        m_inputLayer->setLayerInput(i, input[i]);
    }

    update(-1); // Propagate the input layer first

    // Then propagate the hidden layers
    for (int i = 0; i < m_hiddenLayers.size(); i++) {
        update(i);
    }

    // Last but not least, propagate the output layer (last layer)
    update(m_hiddenLayers.size());
}

void NeuralNetwork::setHiddenLayerWeights(int i, vector<vector<float>> weights, vector<float> biasWeights) {
    m_hiddenLayers[i]->setWeights(weights);
    m_hiddenLayers[i]->setBiasWeights(biasWeights);
}

void NeuralNetwork::setOutputLayerWeights(vector<vector<float>> weights, vector<float> biasWeights) {
    m_outputLayer->setWeights(weights);
    m_outputLayer->setBiasWeights(biasWeights);
}

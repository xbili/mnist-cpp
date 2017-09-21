//
// Created by xbili on 9/15/17.
//

#include <cstring>
#include "NeuralNetwork.h"

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

        m_outputLayer = new Layer(hiddenLayers[hiddenLayerCount - 1], outputCount);
    } else {
        m_outputLayer = new Layer(inputNeurons, outputCount);
    }
}

NeuralNetwork::~NeuralNetwork() {}

float NeuralNetwork::train(const float *desiredOutput, const float *input, float alpha, float momentum) {
    float errorg = 0; // General quadratic error
    float errorc; // Local error
    float sum = 0, csum = 0;
    float delta, udelta;
    float output;

    // Begin by propagating the input
    propagate(input);

    for (int i = 0; i < m_outputLayer->getNeuronCount(); i++) {
        // Calculate error value for the output layer
        output = m_outputLayer->getNeuron(i)->getOutput();

        errorc = (desiredOutput[i] - output) * output * (1 - output);

        // General error is the sum of delta values. Delta: squared quadratic error
        errorg += (desiredOutput[i] - output) * (desiredOutput[i] - output);

        for (int j = 0; j < m_outputLayer->getInputCount(); j++) {
            // Get the current delta value
            delta = m_outputLayer->getNeuron(i)->getDeltaValue(j);

            // Update the delta value
            udelta = alpha * errorc * m_outputLayer->getLayerInput(j) + delta * momentum;

            // Update the weight values
            float currentWeight = m_outputLayer->getNeuron(i)->getWeight(j);
            m_outputLayer->getNeuron(i)->setWeight(j, currentWeight + udelta);
            m_outputLayer->getNeuron(i)->setDeltaValue(j, udelta);

            // Need this to propagate to the next layer
            sum += m_outputLayer->getNeuron(i)->getWeight(j) * errorc;
        }

        // Calculate the weight gain
        m_outputLayer->getNeuron(i)->incrementWgain(
                alpha * errorc * m_outputLayer->getNeuron(i)->getGain());
    }


    for (int i = (m_hiddenLayerCount - 1); i >= 0; i--) {
        for (int j = 0; j < m_hiddenLayers[i]->getNeuronCount(); j++) {
            output = m_hiddenLayers[i]->getNeuron(j)->getOutput();

            // Calculate the error for this layer
            errorc = output * (1 - output) * sum;

            // Update neuron weights
            for (int k = 0; k < m_hiddenLayers[i]->getInputCount(); k++) {
                // Get the current delta value
                delta = m_hiddenLayers[i]->getNeuron(j)->getDeltaValue(k);

                // Update the delta value
                udelta = alpha * errorc * m_hiddenLayers[i]->getLayerInput(k) + delta * momentum;

                // Update the weight values
                float currentWeight = m_hiddenLayers[i]->getNeuron(j)->getWeight(k);
                m_hiddenLayers[i]->getNeuron(j)->setWeight(k, currentWeight + udelta);
                m_hiddenLayers[i]->getNeuron(j)->setDeltaValue(k, udelta);

                // Need this to propagate to the next layer
                csum += m_hiddenLayers[i]->getNeuron(j)->getWeight(k) * errorc;
            }

            // Calculate the weight gain
            m_hiddenLayers[i]->getNeuron(j)->incrementWgain(
                    alpha * errorc * m_hiddenLayers[i]->getNeuron(j)->getGain());
        }

        sum = csum;
        csum = 0;
    }

    // Process the input layer
    for (int i = 0; i < m_inputLayer->getNeuronCount(); i++) {
        output = m_inputLayer->getNeuron(i)->getOutput();
        errorc = output * (1 - output) * sum;

        for (int j = 0; j < m_inputLayer->getInputCount(); j++) {
            delta = m_inputLayer->getNeuron(i)->getDeltaValue(j);
            udelta = alpha * errorc * m_inputLayer->getLayerInput(j) + delta * momentum;

            // Update weights
            float currentWeight = m_inputLayer->getNeuron(i)->getWeight(j);
            m_inputLayer->getNeuron(i)->setWeight(j, currentWeight + udelta);
            m_inputLayer->getNeuron(i)->setDeltaValue(j, udelta);
        }

        // Update the gain weight
        m_inputLayer->getNeuron(i)->incrementWgain(
                alpha * errorc * m_inputLayer->getNeuron(i)->getGain());
    }

    // return the general error divided by 2
    return errorg / 2;
}

void NeuralNetwork::update(int layerIndex) {
    if (layerIndex == -1) {
        // Dealing with the inputLayer here and propagating to the next layer
        for (int i = 0; i < m_inputLayer->getNeuronCount(); i++) {
            if (m_hiddenLayerCount > 0) {
                m_hiddenLayers[0]->setLayerInput(i, m_inputLayer->getNeuron(i)->getOutput());
            } else {
                m_outputLayer->setLayerInput(i, m_inputLayer->getNeuron(i)->getOutput());
            }
        }
    } else {
        for (int i = 0; i < m_hiddenLayers[layerIndex]->getNeuronCount(); i++) {
            //not the last hidden layer
            if (layerIndex < m_hiddenLayerCount - 1) {
                m_hiddenLayers[layerIndex + 1]->setLayerInput(i, m_hiddenLayers[layerIndex]->getNeuron(i)->getOutput());
            } else {
                m_outputLayer->setLayerInput(i, m_hiddenLayers[layerIndex]->getNeuron(i)->getOutput());
            }
        }
    }
}

void NeuralNetwork::propagate(const float *input) {
    // Propagation should start from the input layer
    // Copy the input vector to the input layer, making sure that the size "array input" has the same size of
    // input count.
    memcpy(
        m_inputLayer->getLayerInputs(),
        input,
        m_inputLayer->getInputCount() * sizeof(float)
    );

    // Calculate the input layer
    m_inputLayer->calculate();

    // Propagate the input layer out values to the next layer
    update(-1);

    // Calculate hidden layers
    if (m_hiddenLayers) {
        // Calculate hidden layers if any
        for (int i = 0; i < m_hiddenLayerCount; i++) {
            m_hiddenLayers[i]->calculate();
            update(i);
        }
    }

    // Calculate output layer
    m_outputLayer->calculate();
}

void NeuralNetwork::loadWeights(float **weights) {
    // Set weights for hidden layers
    for (int i = 0; i < m_hiddenLayerCount; i++) {
        m_hiddenLayers[i]->setWeights(weights[i]);
    }

    // Set weights for output layer
    m_outputLayer->setWeights(weights[m_hiddenLayerCount]);
}

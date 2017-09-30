//
// Created by Xu Bili on 9/30/17.
//

#include <gtest/gtest.h>
#include "../src/Layer.h"
#include "../src/Neuron.h"


class LayerTests : public ::testing::Test {

protected:
    Layer *layer;
    virtual void SetUp() {
        layer = new Layer(4, 4);
    }

    virtual void TearDown() {
        delete(layer);
    }
};


TEST_F(LayerTests, Inititalization) {
    ASSERT_EQ(layer->getNeuronCount(), 4 + 1); // +1 for the bias neuron
    ASSERT_EQ(layer->getInputCount(), 4);
}


TEST_F(LayerTests, SetLayerInput) {
    vector<float> inputs = { 0.1, 0.2, 0.3, 0.4 };
    for (int i = 0; i < inputs.size(); i++) {
        layer->setLayerInput(i, inputs[i]);
    }

    vector<float> layerInputs = layer->getInputs();
    for (int i = 0; i < layerInputs.size(); i++) {
        ASSERT_EQ(layerInputs[i], inputs[i]);
    }
}


TEST_F(LayerTests, SetLayerWeights) {
    vector<vector<float>> weights = {
            { 0.1, 0.2, 0.3, 0.4 },
            { 0.5, 0.6, 0.7, 0.8 },
            { 0.9, 1.0, 1.1, 1.2 },
            { 1.3, 1.4, 1.5, 1.6 }
    };

    vector<float> biasWeights = { 0.1, 0.2, 0.3, 0.4 };

    layer->setWeights(weights);
    layer->setBiasWeights(biasWeights);

    vector<Neuron*> neurons = layer->getNeurons();
    for (int i = 0; i < neurons.size() - 1; i++) { // -1 for the bias neuron
        for (int j = 0; j < 4; j++) {
            ASSERT_EQ(neurons[i]->getWeight(j), weights[i][j]);
        }
    }

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(neurons.back()->getWeight(i), biasWeights[i]);
    }
}

TEST_F(LayerTests, CalculateAllPositiveLayer) {
    vector<float> inputs = { 0.1, 0.2, 0.3, 0.4 };
    vector<vector<float>> weights = {
            { 0.1, 0.2, 0.3, 0.4 },
            { 0.5, 0.6, 0.7, 0.8 },
            { 0.9, 1.0, 1.1, 1.2 },
            { 1.3, 1.4, 1.5, 1.6 }
    };

    vector<float> biasWeights = { 0.1, 0.2, 0.3, 0.4 };

    for (int i = 0; i < inputs.size(); i++) {
        layer->setLayerInput(i, inputs[i]);
    }
    layer->setWeights(weights);
    layer->setBiasWeights(biasWeights);
    layer->calculate();

    vector<float> expected = { 0.3, 0.7, 1.1, 1.5, 1 };
    for (int i = 0; i < expected.size(); i++) {
        ASSERT_FLOAT_EQ(layer->getNeuron(i)->getOutput(), expected[i]);
    }
}


TEST_F(LayerTests, CalculateNegativesLayer) {
    vector<float> inputs = { 0.1, 0.2, 0.3, 0.4 };
    vector<vector<float>> weights = {
            { 0.1, 0.2, 0.3, 0.4 },
            { 0.5, 0.6, 0.7, 0.8 },
            { 0.9, 1.0, 1.1, 1.2 },
            { 1.3, 1.4, 1.5, 1.6 }
    };

    vector<float> biasWeights = { 0.1, 0.2, 0.3, 0.4 };

    for (int i = 0; i < inputs.size(); i++) {
        layer->setLayerInput(i, inputs[i]);
    }
    layer->setWeights(weights);
    layer->setBiasWeights(biasWeights);
    layer->calculate();

    vector<float> expected = { 0.3, 0.7, 1.1, 1.5, 1 };
    for (int i = 0; i < expected.size(); i++) {
        ASSERT_FLOAT_EQ(layer->getNeuron(i)->getOutput(), expected[i]);
    }
}

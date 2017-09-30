//
// Created by Xu Bili on 9/30/17.
//

#include <gtest/gtest.h>
#include "../src/Neuron.h"


class NeuronTest : public ::testing::Test {

protected:
    Neuron *neuron;
    virtual void SetUp() {
        neuron = new Neuron(10);
    }

    virtual void TearDown() {
        delete(neuron);
    }

};

TEST_F(NeuronTest, Inititalization) {
    ASSERT_EQ(neuron->getOutput(), 0);
}


TEST_F(NeuronTest, SetOutput) {
    neuron->setOutput(0.5);
    ASSERT_EQ(neuron->getOutput(), 0.5);
}

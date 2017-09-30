//
// Created by xbili on 9/16/17.
//

#include <string>
#include <vector>

#ifndef MNIST_CPP_DATAREADER_H
#define MNIST_CPP_DATAREADER_H

using namespace std;

class DataReader {

private:
    string m_fileName;
    vector<vector<float>> m_inputs;
    vector<float> m_labels;

public:
    DataReader(string fileName);
    virtual ~DataReader();

    vector<vector<float>> getInputs() const;
    vector<float> getLabels() const;
};


#endif //MNIST_CPP_DATAREADER_H

//
// Created by xbili on 9/16/17.
//

#include <string>

#ifndef MNIST_CPP_DATAREADER_H
#define MNIST_CPP_DATAREADER_H

using std::string;

class DataReader {

private:
    string m_fileName;
    int m_numColumns;
    int m_labelColumn;
    float **m_inputs;
    float *m_labels;

public:
    DataReader(string fileName, int numColumns, int labelColumn, int numRows);

    virtual ~DataReader();

    float **getInputs() const;

    float *getLabels() const;
};


#endif //MNIST_CPP_DATAREADER_H

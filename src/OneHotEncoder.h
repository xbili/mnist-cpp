//
// Created by xbili on 9/16/17.
//

#ifndef MNIST_CPP_ONEHOTENCODER_H
#define MNIST_CPP_ONEHOTENCODER_H

#include <vector>

using namespace std;

class OneHotEncoder {

private:
    int m_categories;
    int m_rows;
    vector<float> m_data;
    vector<vector<float>> m_encoded;

public:
    OneHotEncoder(vector<float> data, int categories, int rows);
    vector<vector<float>> getEncoded() const;

private:
    void encode();
};


#endif //MNIST_CPP_ONEHOTENCODER_H

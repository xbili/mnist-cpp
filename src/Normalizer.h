//
// Created by xbili on 9/21/17.
//

#ifndef MNIST_CPP_NORMALIZER_H
#define MNIST_CPP_NORMALIZER_H

#include <vector>

using namespace std;

class Normalizer {
private:
    vector<vector<float>> m_data;
    vector<vector<float>> m_normalized;
public:
    Normalizer(vector<vector<float>> data);
    vector<vector<float>> getNormalized();
private:
    void normalize();
};


#endif //MNIST_CPP_NORMALIZER_H

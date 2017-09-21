//
// Created by xbili on 9/21/17.
//

#ifndef MNIST_CPP_NORMALIZER_H
#define MNIST_CPP_NORMALIZER_H


class Normalizer {
private:
    float **m_data;
    float **m_normalized;
    int m_features;
    int m_size;
public:
    Normalizer(float **data, int features, int size);
    float **getNormalized();
private:
    void normalize();
};


#endif //MNIST_CPP_NORMALIZER_H

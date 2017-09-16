//
// Created by xbili on 9/16/17.
//

#ifndef MNIST_CPP_ONEHOTENCODER_H
#define MNIST_CPP_ONEHOTENCODER_H


class OneHotEncoder {

private:
    int m_categories;
    int m_rows;
    float* m_data;
    float** m_encoded;

public:
    OneHotEncoder(float *data, int categories, int rows);
    float **getEncoded() const;

private:
    void encode();
};


#endif //MNIST_CPP_ONEHOTENCODER_H

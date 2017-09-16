//
// Created by xbili on 9/16/17.
//

#include "OneHotEncoder.h"

OneHotEncoder::OneHotEncoder(float *data, int categories, int rows) :
        m_data(data),
        m_categories(categories),
        m_rows(rows) {
    m_encoded = new float*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_encoded[i] = new float[m_categories];
    }

    encode();
}

float **OneHotEncoder::getEncoded() const {
    return m_encoded;
}

void OneHotEncoder::encode() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_categories; j++) {
            if (j == m_data[i]) {
                m_encoded[i][j] = 1;
            } else {
                m_encoded[i][j] = 0;
            }
        }
    }
}

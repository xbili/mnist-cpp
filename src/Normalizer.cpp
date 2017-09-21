//
// Created by xbili on 9/21/17.
//
#include <algorithm>

#include "Normalizer.h"

Normalizer::Normalizer(float** data, int features, int size) : m_data(data), m_features(features), m_size(size) {
    // Allocate space for the normalized data
    m_normalized = new float*[size];
    for (int i = 0; i < size; i++) {
        m_normalized[i] = new float[features];
    }

    normalize();
}

float **Normalizer::getNormalized() {
    return m_normalized;
}

void Normalizer::normalize() {
    for (int i = 0; i < m_size; i++) {
        auto minmax = std::minmax(m_data[i][0], m_data[i][m_features-1]);

        // Update the value in each row to be equals to the normalized value
        for (int j= 0; j < m_features; j++) {
            m_normalized[i][j] = (m_data[i][j] - minmax.first) / (minmax.second - minmax.first);
        }
    }
}

//
// Created by xbili on 9/21/17.
//
#include <algorithm>

#include "Normalizer.h"

Normalizer::Normalizer(vector<vector<float>> data) : m_data(data) {
    normalize();
}

vector<vector<float>> Normalizer::getNormalized() {
    return m_normalized;
}

void Normalizer::normalize() {
    for (int i = 0; i < m_data.size(); i++) {
        float max = *max_element(m_data[i].begin(), m_data[i].end());
        float min = *min_element(m_data[i].begin(), m_data[i].end());

        vector<float> row;
        for (int j = 0; j < m_data[i].size(); j++) {
            float res = (m_data[i][j] - min) / (max - min);
            m_normalized[i].push_back(res);
        }

        m_normalized.push_back(row);
    }
}

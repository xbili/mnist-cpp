//
// Created by xbili on 9/16/17.
//

#include "OneHotEncoder.h"

OneHotEncoder::OneHotEncoder(vector<float> data, int categories, int rows) :
        m_data(data),
        m_categories(categories),
        m_rows(rows) {
    encode();
}

vector<vector<float>> OneHotEncoder::getEncoded() const {
    return m_encoded;
}

void OneHotEncoder::encode() {
    for (int i = 0; i < m_data.size(); i++) {
        vector<float> row(m_categories, 0);
        for (int j = 0; j < m_categories; j++) {
            if (j == m_data[i]) {
                row[j] = 1;
            } else {
                row[j] = 0;
            }
        }
        m_encoded.push_back(row);
    }
}

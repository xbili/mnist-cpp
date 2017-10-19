//
// Created by xbili on 10/19/17.
//

#include <assert.h>
#include "LinearAlg.h"

float LinearAlg::dotProduct(vector<float> a, vector<float> b) {
    // Sizes of the vectors should be the same
    assert(a.size() == b.size());

    float sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += a[i] * b[i];
    }

    return sum;
}

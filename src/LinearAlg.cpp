//
// Created by xbili on 10/19/17.
//

#include <assert.h>
#include <cstdint>
#include "LinearAlg.h"

float LinearAlg::dotProduct(vector<float> a, vector<float> b) {
    // Sizes of the vectors should be the same
    assert(a.size() == b.size());

    int sum = 0;
    for (int i = 0; i < a.size(); i++) {
        int8_t quantizedA = (int8_t) (a[i] * 10);
        int8_t quantizedB = (int8_t) (b[i] * 10);
        sum += quantizedA * quantizedB;
    }

    float back = (float) sum;

    return back / 10;
}

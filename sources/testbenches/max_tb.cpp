/* 
 * Copyright © 2021 "DrasLorus"
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * file and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../modules/max.hpp"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(int, char **) {
    srand(time(nullptr));

    vector<uint8_t> to_be_maxed64(64, 0);
    for (auto && it : to_be_maxed64) {
        it = uint8_t(floor(float(rand()) / float(RAND_MAX) * 256.f));
    }

    vector<uint8_t> to_be_maxed63(63, 0);
    for (auto && it : to_be_maxed63) {
        it = uint8_t(floor(float(rand()) / float(RAND_MAX) * 256.f));
    }

    vector<float> to_be_maxed64f(64, 0);
    for (auto && it : to_be_maxed64f) {
        it = float(rand()) / float(RAND_MAX) * 1000.f;
    }

    vector<float> to_be_maxed63f(63, 0);
    for (auto && it : to_be_maxed63f) {
        it = float(rand()) / float(RAND_MAX) * 1000.f;
    }

    const uint8_t max64_value  = do_max_64(to_be_maxed64.data());
    // const uint8_t max63_value  = do_max_63(to_be_maxed63.data());
    // const float   max64f_value = do_max_64f(to_be_maxed64f.data());
    // const float   max63f_value = do_max_63f(to_be_maxed63f.data());

    // cout << unsigned(max64_value) << " " << unsigned(max63_value) << endl;
    // cout << float(max64f_value) << " " << float(max63f_value) << endl;

    int retval = 0;

    const uint8_t max_64_test  = *max_element(to_be_maxed64.begin(), to_be_maxed64.end());
    // const uint8_t max_63_test  = *max_element(to_be_maxed63.begin(), to_be_maxed63.end());
    // const float   max_64f_test = *max_element(to_be_maxed64f.begin(), to_be_maxed64f.end());
    // const float   max_63f_test = *max_element(to_be_maxed63f.begin(), to_be_maxed63f.end());

    retval += (max_64_test == max64_value ? 0 : 1);
    // retval += (max_63_test == max63_value ? 0 : 1);
    // retval += (max_64f_test == max64f_value ? 0 : 1);
    // retval += (max_63f_test == max63f_value ? 0 : 1);

    cout << (retval == 0 ? "Test passed. " : "Test failed. ") << unsigned(max_64_test) << " vs " << unsigned(max64_value) << endl;

    return retval;
}

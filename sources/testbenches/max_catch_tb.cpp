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

#include <catch2/catch.hpp>

using std::max_element;
using std::vector;

TEST_CASE("Factorials are computed", "[factorial]") {
    srand(time(nullptr));

    vector<uint8_t> to_be_maxed64(64 * 8, 0);
    for (auto && it : to_be_maxed64) {
        it = uint8_t(floor(float(rand()) / float(RAND_MAX) * 256.f));
    }

    for (unsigned u = 0; u < to_be_maxed64.size() - 64; u++) {
        const uint8_t * local_beg = to_be_maxed64.data() + u;
        const uint8_t * local_end = local_beg + 64;

        const uint8_t max64_value = do_max_64(local_beg);
 
        const uint8_t max_64_test = *max_element(local_beg, local_end);

        REQUIRE(max_64_test == max64_value);
    }

    // cout << (retval == 0 ? "Test passed. " : "Test failed. ") << endl;
}

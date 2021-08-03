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
#include <string>
#include <vector>

#include <matio.h>

#include <catch2/catch.hpp>

using std::max_element;
using std::string;
using std::vector;
using std::cerr;
using std::endl;

TEST_CASE("Factorials are computed", "[factorial]") {
    string in_file("../data/input.mat");

    mat_t * mfile = Mat_Open(in_file.c_str(), MAT_ACC_RDONLY);
    REQUIRE(bool(mfile));


    matvar_t * pdata = Mat_VarRead(mfile, "data");
    REQUIRE(bool(pdata));

    uint16_t * data = (uint16_t *) pdata->data;

    vector<uint16_t> in_data(data, data + pdata->dims[1]);

    Mat_VarFree(pdata);
    Mat_Close(mfile);

    for (unsigned u = 0; u < in_data.size() - 127; u+=64) {
        const uint16_t * local_beg     = in_data.data() + u;
        const uint16_t * local_end_64  = local_beg + 64;
        const uint16_t * local_end_127 = local_beg + 127;

        const uint16_t max64_redx = do_max_redx_64(local_beg);
        const uint16_t max64_tail = do_max_tail_64(local_beg);
        const uint16_t max64_head = do_max_head_64(local_beg);
        const uint16_t max64_loop = do_max_loop_64(local_beg);

        const uint16_t max127_redx = do_max_redx_127(local_beg);
        const uint16_t max127_tail = do_max_tail_127(local_beg);
        const uint16_t max127_head = do_max_head_127(local_beg);
        const uint16_t max127_loop = do_max_loop_127(local_beg);

        const uint16_t max_64_test  = *max_element(local_beg, local_end_64);
        const uint16_t max_127_test = *max_element(local_beg, local_end_127);

        REQUIRE(max_64_test == max64_redx);
        REQUIRE(max_64_test == max64_tail);
        REQUIRE(max_64_test == max64_head);
        REQUIRE(max_64_test == max64_loop);
        REQUIRE(max_127_test == max127_redx);
        REQUIRE(max_127_test == max127_tail);
        REQUIRE(max_127_test == max127_head);
        REQUIRE(max_127_test == max127_loop);
    }

    // cout << (retval == 0 ? "Test passed. " : "Test failed. ") << endl;
}

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

using namespace std;

int main(int argc, char ** argv) {

    string in_file("../data/input.mat");

    if (argc > 1) {
        in_file = string(argv[1]);
    }

    mat_t * mfile = Mat_Open(in_file.c_str(), MAT_ACC_RDONLY);
    if (!bool(mfile)) {
        cerr << "Error while opening " << in_file << "." << endl;
        return EXIT_FAILURE;
    }

    matvar_t * pdata = Mat_VarRead(mfile, "data");
    if (!bool(pdata)) {
        cerr << "Error while opening " << in_file << "." << endl;
        return EXIT_FAILURE;
    }

    uint16_t * data = (uint16_t *) pdata->data;

    vector<uint16_t> in_data(data, data + pdata->dims[1]);

    Mat_VarFree(pdata);
    Mat_Close(mfile);

    // vector<uint8_t> to_be_maxed63(63, 0);
    // for (auto && it : to_be_maxed63) {
    //     it = uint8_t(floor(float(rand()) / float(RAND_MAX) * 256.f));
    // }

    // vector<float> to_be_maxed64f(64, 0);
    // for (auto && it : to_be_maxed64f) {
    //     it = float(rand()) / float(RAND_MAX) * 1000.f;
    // }

    // vector<float> to_be_maxed63f(63, 0);
    // for (auto && it : to_be_maxed63f) {
    //     it = float(rand()) / float(RAND_MAX) * 1000.f;
    // }

    int retval = 0;
    for (unsigned u = 0; u < in_data.size(); u += 64) {
        const uint16_t * local_beg = in_data.data() + u;
        const uint16_t * local_end = local_beg + 64;

        const uint16_t max64_value = do_max_redx_64(local_beg);
        // const uint8_t max63_value  = do_max_63(to_be_maxed63.data());
        // const float   max64f_value = do_max_64f(to_be_maxed64f.data());
        // const float   max63f_value = do_max_63f(to_be_maxed63f.data());

        // cout << unsigned(max64_value) << " " << unsigned(max63_value) << endl;
        // cout << float(max64f_value) << " " << float(max63f_value) << endl;

        const uint16_t max_64_test = *max_element(local_beg, local_end);
        // const uint8_t max_63_test  = *max_element(to_be_maxed63.begin(), to_be_maxed63.end());
        // const float   max_64f_test = *max_element(to_be_maxed64f.begin(), to_be_maxed64f.end());
        // const float   max_63f_test = *max_element(to_be_maxed63f.begin(), to_be_maxed63f.end());

        retval += (max_64_test == max64_value ? 0 : 1);
        // cout << max_64_test << " == " << max64_value << endl;
        // retval += (max_63_test == max63_value ? 0 : 1);
        // retval += (max_64f_test == max64f_value ? 0 : 1);
        // retval += (max_63f_test == max63f_value ? 0 : 1);
    }

    cout << (retval == 0 ? "Test passed. " : "Test failed. ") << endl;

    return retval;
}

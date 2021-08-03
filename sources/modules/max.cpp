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

#include "max.hpp"
#include <iostream>

#ifdef _MAX_IS_TOP_

uint16_t do_max_redx_64(const uint16_t in_array[64]) {

    //#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[64];


#pragma HLS array_partition variable = in_array complete
#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 64; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_pow2<64>::process(load_array);
}

uint16_t do_max_tail_64(const uint16_t in_array[64]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[64];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 64; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<64, TAILED>::process(load_array);
}

uint16_t do_max_head_64(const uint16_t in_array[64]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[64];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 64; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<64, HEADED>::process(load_array);
}

uint16_t do_max_loop_64(const uint16_t in_array[64]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[64];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 64; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<64, LOOPED>::process(load_array);
}

uint16_t do_max_redx_127(const uint16_t in_array[127]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[127];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 127; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<127>::process(load_array);
}

uint16_t do_max_tail_127(const uint16_t in_array[127]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[127];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 127; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<127, TAILED>::process(load_array);
}

uint16_t do_max_head_127(const uint16_t in_array[127]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[127];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 127; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<127, HEADED>::process(load_array);
}

uint16_t do_max_loop_127(const uint16_t in_array[127]) {

#pragma HLS interface ap_memory port = in_array

    uint16_t load_array[127];

#pragma HLS array_partition variable = load_array complete

    for (uint16_t u = 0; u < 127; u++) {

#pragma HLS unroll
        load_array[u] = in_array[u];
    }

    return max_template<127, LOOPED>::process(load_array);
}

#endif

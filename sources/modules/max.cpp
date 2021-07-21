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

#define IS_EVEN(N)      (((N >> 1) << 1) == N)

// uint8_t do_max_63(const uint8_t in_array[63]) {
// #pragma HLS interface ap_memory port=in_array

//    uint8_t load_array[63];
// #pragma HLS array_partition variable=load_array complete

//    for (uint8_t u = 0; u < 63; u++){
// #pragma HLS unroll
//        load_array[u] = in_array[u];
//    }

//    return max_template<63>::process(load_array);
// }

uint8_t do_max_64(const uint8_t in_array[64]) {
#pragma HLS interface ap_memory port=in_array

   uint8_t load_array[64];
#pragma HLS array_partition variable=load_array complete

   for (uint8_t u = 0; u < 64; u++){
#pragma HLS unroll
       load_array[u] = in_array[u];
   }

   return max_pow2<64>::process(load_array);
}

// float do_max_63f(const float in_array[63]) {
// #pragma HLS interface ap_memory port=in_array

//    float load_array[63];
// #pragma HLS array_partition variable=load_array complete

//    for (uint8_t u = 0; u < 63; u++){
// #pragma HLS unroll
//        load_array[u] = in_array[u];
//    }

//    return max_template<63>::process(load_array);
// }

// float do_max_64f(const float in_array[64]) {
// #pragma HLS interface ap_memory port=in_array

//    float load_array[64];
// #pragma HLS array_partition variable=load_array complete

//    for (uint8_t u = 0; u < 64; u++){
// #pragma HLS unroll
//        load_array[u] = in_array[u];
//    }

//    return max_pow2<64>::process(load_array);
// }

#endif

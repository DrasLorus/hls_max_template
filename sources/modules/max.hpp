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

#ifndef _MAX_TEMPLATE_HPP_
#define _MAX_TEMPLATE_HPP_ 1

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#ifdef _MAX_IS_TOP_

uint16_t do_max_redx_64(const uint16_t in_array[64]);
uint16_t do_max_tail_64(const uint16_t in_array[64]);
uint16_t do_max_head_64(const uint16_t in_array[64]);
uint16_t do_max_loop_64(const uint16_t in_array[64]);
uint16_t do_max_redx_127(const uint16_t in_array[64]);
uint16_t do_max_tail_127(const uint16_t in_array[64]);
uint16_t do_max_head_127(const uint16_t in_array[64]);
uint16_t do_max_loop_127(const uint16_t in_array[64]);

#endif

template <unsigned N>
struct max_pow2 {
    template <typename T>
    static T process(const T values[N]) {
        static_assert(N > 2, "N cannot be less than 3!");
        T half_values[N / 2];
#pragma HLS array_partition variable = half_values complete
        for (uint8_t i = 0; i < N / 2; i++) {
#pragma HLS unroll
            const uint8_t j   = i << 1;
            const uint8_t jp1 = j + 1;
            half_values[i]    = (values[j] < values[jp1] ? values[jp1] : values[j]);
        }
        return max_pow2<N / 2>::process(half_values);
    }
};

template <>
struct max_pow2<2> {
    template <typename T>
    static T process(const T values[2]) {
        return (values[0] < values[1] ? values[1] : values[0]);
    }
};

/* TRUE MAX TEMPLATE BELOW */

/**
 * @brief Defines supported schedules
 * 
 */
typedef enum {
    REDUCED,
    LOOPED,
    TAILED,
    HEADED
} max_type_t;

/* REDUCED *****************/

/**
 * @brief Recursive template to implement a completely reduced scheduling
 * 
 * @tparam N     Input size
 * @tparam bEven True if N is even, false otherwise.
 *               Can use the Macro IS_EVEN()
 */
template <unsigned N, bool bEven>
class max_reduced {
public:
    template <typename T>
    static T process(const T values[N]);
};

/* REDUCED when N is even */

template <unsigned N>
class max_reduced<N, true> {
private:
    static constexpr unsigned half = N >> 1;

public:
    template <typename T>
    static T process(const T values[N]);
};

/* REDUCED when N is odd */

template <unsigned N>
class max_reduced<N, false> {
private:
    static constexpr unsigned Nm1    = N - 1;
    static constexpr unsigned half   = (Nm1 >> 1);
    static constexpr unsigned halfp1 = half + 1;

public:
    template <typename T>
    static T process(const T values[N]);
};

template <>
class max_reduced<1, false> {

public:
    template <typename T>
    static T process(const T values[1]) {
        return values[0];
    }
};

template <>
class max_reduced<2, true> {

public:
    template <typename T>
    static T process(const T values[2]) {
        return (values[0] < values[1] ? values[1] : values[0]);
    }
};

template <>
class max_reduced<3, false> {

public:
    template <typename T>
    static T process(const T values[3]) {
        const T max2 = (values[0] < values[1] ? values[1] : values[0]);
        return (values[2] < max2 ? max2 : values[2]);
    }
};

#define IS_EVEN(N) (((N >> 1) << 1) == N)

template <unsigned N>
template <typename T>
T max_reduced<N, true>::process(const T values[N]) {
    static_assert(N > 2, "N cannot be less than 3!");
    T half_values[half];
    loop_redx_max:
    for (uint8_t i = 0; i < half; i++) {
        const uint8_t j   = i << 1;
        const uint8_t jp1 = j + 1;
        half_values[i]    = (values[j] < values[jp1] ? values[jp1] : values[j]);
    }
    return max_reduced<half, IS_EVEN(half)>::process(half_values);
}

template <unsigned N>
template <typename T>
T max_reduced<N, false>::process(const T values[N]) {
    static_assert(N > 3, "N cannot be less than 3!");
    T half_values[halfp1];
#pragma HLS array_partition variable=half_values complete
    for (uint8_t i = 0; i < half; i++) {
#pragma HLS unroll
        const uint8_t j   = i << 1;
        const uint8_t jp1 = j + 1;
        half_values[i]    = (values[j] < values[jp1] ? values[jp1] : values[j]);
    }
    half_values[half] = values[Nm1];
    return max_reduced<halfp1, IS_EVEN(halfp1)>::process(half_values);
}

/**
 * @brief User friendly max template
 * 
 * @tparam N    Input Size
 * @tparam Ver  Schedule wanted. Default: REDUCED 
 */
template <unsigned N, max_type_t Ver = REDUCED>
class max_template : public max_reduced<N, IS_EVEN(N)> {
};

template <>
class max_template<1, TAILED> {
public:
    template <typename T>
    static T process(const T values[1]) {
        return values[0];
    }
};

template <>
class max_template<2, TAILED> {
public:
    template <typename T>
    static T process(const T values[2]) {
        return (values[0] < values[1] ? values[1] : values[0]);
    }
};

template <unsigned N>
class max_template<N, TAILED> {
private:
    static constexpr unsigned Nm1 = N - 1;

public:
    template <typename T>
    static T process(const T values[N]) {
        const T max_Nm1 = max_template<Nm1, TAILED>::process(values);
        return (max_Nm1 < values[Nm1] ? values[Nm1] : max_Nm1);
    }
};

template <>
class max_template<1, HEADED> {
public:
    template <typename T>
    static T process(const T values[1]) {
        return values[0];
    }
};

template <>
class max_template<2, HEADED> {
public:
    template <typename T>
    static T process(const T values[2]) {
        return (values[0] < values[1] ? values[1] : values[0]);
    }
};

template <unsigned N>
class max_template<N, HEADED> {
private:
    static constexpr unsigned Nm1 = N - 1;

public:
    template <typename T>
    static T process(const T values[N]) {
        const T max_Nm1 = max_template<Nm1, HEADED>::process(values + 1);
        return (max_Nm1 < values[0] ? values[0] : max_Nm1);
    }
};

template <unsigned N>
class max_template<N, LOOPED> {

public:
    template <typename T>
    static T process(const T values[N]) {
        T max_value = values[0];
    loop_max:
        for (unsigned u = 1; u < N; u++) {
            const T value = values[u];
            max_value     = (max_value < value ? value : max_value);
        }
        return max_value;
    }
};

#undef IS_EVEN

#endif // _MAX_TEMPLATE_HPP_

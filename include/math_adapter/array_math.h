/*
 * MIT License
 *
 * Copyright (c) 2023 Chang Guo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef SEISTOOLS_C_ARRAY_MATH_H
#define SEISTOOLS_C_ARRAY_MATH_H

#include <math.h>
#include "../basic/array_template.h"

// sum

#define array_template_sum_declaration(T) T array_##T##_sum(Array(T) arr)

#define array_template_sum_definition(T) array_template_sum_declaration(T){ \
    uint64 i, n; \
    T v; \
    v = (T)0; \
    n = array_inner_ivec_product(arr.s); \
    for(i=0; i<n; i++) v += arr.v[i]; \
    return v; \
}

// mean

#define array_template_mean_declaration(S, T) S array_##T##_mean(Array(T) arr)

#define array_template_mean_definition(S, T) array_template_mean_declaration(S,T){ \
    return ((S)array_##T##_sum(arr))/((S)array_inner_ivec_product(arr.s)); \
}

// var

#define array_template_var_declaration(S, T) S array_##T##_var(Array(T) arr, S correct)

#define array_template_var_definition(S, T) array_template_var_declaration(S,T){ \
    S v, m; \
    uint64 i, n; \
    m = (S)0; \
    n = array_inner_ivec_product(arr.s); \
    for( i = 0; i < n; i++ ) m += (S)arr.v[i]; \
    m /= n; \
    v = (S)0; \
    for( i = 0; i < n; i++ ) v += ((S)arr.v[i] - m) * ((S)arr.v[i] - m); \
    v /= ((S)n - correct); \
    return v; \
}

// std

#define array_template_std_declaration(S, T) S array_##T##_std(Array(T) arr, S correct)

#define array_template_std_definition(S, T) array_template_std_declaration(S,T){ \
    return (S)sqrtl(array_##T##_var(arr, correct)); \
}


#endif //SEISTOOLS_C_ARRAY_MATH_H

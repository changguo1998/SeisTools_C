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

#define vector_template_sum_declaration(T) T vector_##T##_sum(Vector(T) vec)

#define vector_template_sum_definition(T) vector_template_sum_declaration(T){ \
    uint64 i; \
    T v; \
    v = (T)0; \
    for(i=0; i<vec.n; i++) v += vector_get(vec, i); \
    return v; \
}

#define vector_template_mean_declaration(S, T) S vector_##T##_mean(Vector(T) vec)

#define vector_template_mean_definition(S, T) vector_template_mean_declaration(S, T){ \
    return (S)vector_##T##_sum(vec)/(S)vec.n; \
}

// var

#define vector_template_var_declaration(S, T) S vector_##T##_var(Vector(T) vec, S correct)

#define vector_template_var_definition(S, T) vector_template_var_declaration(S, T){ \
    uint64 i; \
    S m, v; \
    m = vector_##T##_mean(vec); \
    v = (S)0; \
    for(i=0; i<vec.n; i++) v += (vector_get(vec, i)-m)*(vector_get(vec, i)-m); \
    return v/((S)vec.n - correct); \
}

// std

#define vector_template_std_declaration(S, T) S vector_##T##_std(Vector(T) vec, S correct)

#define vector_template_std_definition(S, T) vector_template_std_declaration(S, T){ \
    return (S)sqrtl(vector_##T##_var(vec, correct)); \
}

// sort

#define vector_template_sort_declaration(T) Vector(uint64) vector_##T##_sort_(Vector(T) vec)

#define vector_template_sort_definition(T) vector_template_sort_declaration(T){ \
    uint64 i, j, ibuff; \
    T ebuff; \
    Vector(uint64) perm; \
    perm = vector_uint64_alloc(vec.n); \
    for(i=0; i<vec.n; i++) vector_get(vec, i) = i; \
    for(i=0; i<vec.n-1; i++) \
        for(j=i+1; j<vec.n; j++) \
            if(vector_get(vec, i)>vector_get(vec, j)){ \
                ebuff = vector_get(vec, i); \
                vector_get(vec, i) = vector_get(vec, j); \
                vector_get(vec, j) = ebuff; \
                ibuff = vector_get(perm, i); \
                vector_get(perm, i) = vector_get(perm, j); \
                vector_get(perm, j) = ibuff; \
            } \
    return perm; \
}

// sum

#define array_template_sum_declaration(T) T array_##T##_sum(Array(T) arr)

#define array_template_sum_definition(T) array_template_sum_declaration(T){ \
    uint64 i, n; \
    T v; \
    v = (T)0; \
    n = vector_uint64_product(arr.s); \
    for(i=0; i<n; i++) v += arr.v[i]; \
    return v; \
}

// mean

#define array_template_mean_declaration(S, T) S array_##T##_mean(Array(T) arr)

#define array_template_mean_definition(S, T) array_template_mean_declaration(S,T){ \
    return ((S)array_##T##_sum(arr))/((S)vector_uint64_product(arr.s)); \
}

// var

#define array_template_var_declaration(S, T) S array_##T##_var(Array(T) arr, S correct)

#define array_template_var_definition(S, T) array_template_var_declaration(S,T){ \
    S v, m; \
    uint64 i, n; \
    m = (S)0; \
    n = vector_uint64_product(arr.s); \
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

// sort

#define array_template_sort_declaration(T) Array(uint64) array_##T##_sort_(Array(T) arr)

#define array_template_sort_definition(T) array_template_sort_declaration(T){ \
    uint64 i, j, n, ibuff; \
    T ebuff; \
    Array(uint64) perm; \
    perm = array_uint64_alloc(arr.s); \
    n = vector_uint64_product(arr.s); \
    for(i=0; i<n; i++) perm.v[i] = i; \
    for(i=0; i<n-1; i++) \
        for(j=i+1; j<n; j++) \
            if(arr.v[i]>arr.v[j]){ \
                ebuff = arr.v[i]; \
                arr.v[i] = arr.v[j]; \
                arr.v[j] = ebuff; \
                ibuff = perm.v[i]; \
                perm.v[i]=perm.v[j]; \
                perm.v[j]=ibuff; \
            } \
    return perm; \
}

// product

#define array_template_product_A_B_declaration(T) Array(T) array_##T##_product_AB(Array(T) A, Array(T) B)

#define array_template_product_A_B_definition(T) array_template_product_A_B_declaration(T){ \
    uint64 i;                                                                               \
    Vector(uint64) size, cA, cB, cC;                                                                    \
    Array(T) C;                                                                             \
    size = vector_uint64_alloc(A.s.n+B.s.n-2);                                              \
    cA = vector_uint64_alloc(A.s.n);                                                        \
    cB = vector_uint64_alloc(B.s.n);                                                        \
    cC = vector_uint64_dcopy(size);\
    for(i=0; i<A.s.n-1; i++) vector_get(size, i) = vector_get(A.s, i);                      \
    for(i=0; i<B.s.n-1; i++) vector_get(size, i+A.s.n-1) = vector_get(B.s, i);              \
    C = array_##T##_alloc(size);                                                            \
    }

//

#define array_template_math_collection_declaration(S, T) vector_template_sum_declaration(T); \
vector_template_mean_declaration(S, T); \
vector_template_var_declaration(S, T); \
vector_template_std_declaration(S, T); \
vector_template_sort_declaration(T); \
array_template_sum_declaration(T); \
array_template_mean_declaration(S, T); \
array_template_var_declaration(S, T); \
array_template_std_declaration(S, T); \
array_template_sort_declaration(T);

#define array_template_math_collection_definition(S, T) vector_template_sum_definition(T) \
vector_template_mean_definition(S, T) \
vector_template_var_definition(S, T) \
vector_template_std_definition(S, T) \
vector_template_sort_definition(T) \
array_template_sum_definition(T) \
array_template_mean_definition(S, T) \
array_template_var_definition(S, T) \
array_template_std_definition(S, T) \
array_template_sort_definition(T)

array_template_math_collection_declaration(float, int)

array_template_math_collection_declaration(double, uint64)

array_template_math_collection_declaration(double, int64)

array_template_math_collection_declaration(float, float)

array_template_math_collection_declaration(double, double)

#endif //SEISTOOLS_C_ARRAY_MATH_H

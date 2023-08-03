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

#ifndef SEISTOOLS_C_ARRAY_TEMPLATE_H
#define SEISTOOLS_C_ARRAY_TEMPLATE_H

#include "basic_types.h"

#define ARRAY_CHECK_BOUNDARY

#define array_m_vector_get(vec, i) ((vec).v[(i)])

#define array_m_vector_set_(vec, i, val) array_m_vector_get(vec, i) = (val)

typedef struct array_inner_used_vector{
    uint64 n, *v;
} array_inner_ivec_t;

array_inner_ivec_t array_inner_ivec_alloc(uint64 n);

array_inner_ivec_t array_inner_ivec_dcopy(array_inner_ivec_t iv);

void array_inner_ivec_free_(array_inner_ivec_t *iv);

uint64 array_inner_ivec_product(array_inner_ivec_t iv);

uint64 array_inner_ivec_cart2lin(array_inner_ivec_t coor, array_inner_ivec_t size);

void array_inner_ivec_lin2cart_(array_inner_ivec_t coor, uint64 lin, array_inner_ivec_t size);

// !------------------------------------------------------------

#define array_get_1d(arr, i0) ((arr).v[(i0)])

#define array_get_2d(arr, i0, i1) ((arr).v[(i0) + (i1)*((arr).s.v[0])])

#define array_get_3d(arr, i0, i1, i2) ((arr).v[\
(i0) + \
((i1) + (i2) * ((arr).s.v[1])) \
*((arr).s.v[0])])

#define array_get_4d(arr, i0, i1, i2, i3) ((arr).v[\
(i0) + \
    ((i1) + \
        ((i2) + (i3) * ((arr).s.v[2])) \
    * ((arr).s.v[1])) \
*((arr).s.v[0])])

#define array_get_5d(arr, i0, i1, i2, i3, i4) ((arr).v[\
(i0) + \
    ((i1) + \
        ((i2) + \
            ((i3) + (i4)*((arr).s.v[3])) \
        * ((arr).s.v[2])) \
    * ((arr).s.v[1])) \
*((arr).s.v[0])])

#define Array(T) Array_##T

#define array_template_type_definition(T) typedef struct array_##T##_t{ \
    array_inner_ivec_t s; \
    T *v; \
} Array(T);

// alloc

#define array_template_alloc_declaration(T) Array(T) array_##T##_alloc(array_inner_ivec_t s)

#define array_template_alloc_definition(T) array_template_alloc_declaration(T){ \
    Array(T) _arr;                                                  \
    _arr.s = array_inner_ivec_dcopy(s);                             \
    _arr.v = (T *)malloc(array_inner_ivec_product(s) * sizeof(T));  \
    return _arr;                                                    \
}

// free

#define array_template_free_declaration(T) void array_##T##_free_(Array(T) *arr)

#define array_template_free_definition(T) array_template_free_declaration(T){ \
    if(arr->v != NULL) free(arr->v);    \
    arr->v = NULL;                      \
    array_inner_ivec_free_(&(arr->s));  \
}

// get value

#define array_template_get_declaration(T) T array_##T##_get(Array(T) arr, array_inner_ivec_t coor)

#define array_template_get_definition(T)  array_template_get_declaration(T){ \
    return arr.v[array_inner_ivec_cart2lin(coor, arr.s)]; \
}

// set value

#define array_template_set_declaration(T) void array_##T##_set_(Array(T) arr, array_inner_ivec_t coor, T val)

#define array_template_set_definition(T) array_template_set_declaration(T){ \
    arr.v[array_inner_ivec_cart2lin(coor, arr.s)] = val;    \
    return;                                                 \
}

// slice

// map

// macro set

#define array_template_collection_declaration(T) array_template_type_definition(T) \
array_template_alloc_declaration(T); \
array_template_free_declaration(T); \
array_template_get_declaration(T); \
array_template_set_declaration(T);

#define array_template_collection_definition(T) array_template_alloc_definition(T) \
array_template_free_definition(T) \
array_template_get_definition(T) \
array_template_set_definition(T)

array_template_collection_declaration(int)

array_template_collection_declaration(int64)

array_template_collection_declaration(float)

array_template_collection_declaration(double)

#endif //SEISTOOLS_C_ARRAY_TEMPLATE_H

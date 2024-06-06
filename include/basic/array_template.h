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

#define vector_get(vec, i) ((vec).v[(i)])

#define Vector(T) Vector_##T

#define vector_template_type_definition(T) typedef struct vector_##T##_t{ \
    UInt n; \
    T *v; \
} Vector(T);

// alloc

#define vector_template_alloc_declaration(T) Vector(T) vector_##T##_alloc(UInt n)

#define vector_template_alloc_definition(T) vector_template_alloc_declaration(T){ \
    Vector(T) _vec;                                                               \
    _vec.n = n;                                                                   \
    _vec.v = (T *)malloc(n * sizeof(T));                                          \
    return _vec;                                                                      \
}

// dcopy

#define vector_template_dcopy_declaration(T) Vector(T) vector_##T##_dcopy(Vector(T) arr)

#define vector_template_dcopy_definition(T) vector_template_dcopy_declaration(T){ \
    Vector(T) _arr;                                                               \
    _arr = vector_##T##_alloc(arr.n);                                             \
    memcpy(_arr.v, arr.v, arr.n * sizeof(T));                                     \
    return _arr;                                                                  \
}

// read

#define vector_template_read_declaration(T) Vector(T) vector_##T##_read(int fid)

#define vector_template_read_definition(T) vector_template_read_declaration(T){ \
    Vector(T) _vec; \
    read(fid, &(_vec.n), sizeof(UInt)); \
    _vec.v = (T *)malloc(_vec.n * sizeof(T)); \
    read(fid, _vec.v, _vec.n*sizeof(T)); \
    return _vec; \
}

// write

#define vector_template_write_declaration(T) void vector_##T##_write(int fid, Vector(T) vec)

#define vector_template_write_definition(T) vector_template_write_declaration(T){ \
    write(fid, &(vec.n), sizeof(UInt)); \
    write(fid, vec.v, vec.n * sizeof(T)); \
}

// free

#define vector_template_free_declaration(T) void vector_##T##_free_(Vector(T) *arr)

#define vector_template_free_definition(T) vector_template_free_declaration(T){ \
    if(arr->v != NULL) free(arr->v);                                            \
    arr->v = NULL;                                                              \
    arr->n = 0;                                                                 \
}

#define vector_template_product_declaration(T) T vector_##T##_product(Vector(T) arr)

#define vector_template_product_definition(T) vector_template_product_declaration(T){ \
    UInt i;                                                                         \
    T v;                                                                              \
    v = (T)1;                                                                         \
    for(i=0; i<arr.n; i++) v *= vector_get(arr, i);                                   \
    return v;                                                                         \
    }


#define vector_template_collection_declaration(T) vector_template_type_definition(T)\
vector_template_alloc_declaration(T); \
vector_template_dcopy_declaration(T); \
vector_template_read_declaration(T); \
vector_template_write_declaration(T); \
vector_template_free_declaration(T); \
vector_template_product_declaration(T);

#define vector_template_collection_definition(T) \
vector_template_alloc_definition(T) \
vector_template_dcopy_definition(T) \
vector_template_read_definition(T) \
vector_template_write_definition(T) \
vector_template_free_definition(T) \
vector_template_product_definition(T)

vector_template_collection_declaration(Int)

vector_template_collection_declaration(UInt)

vector_template_collection_declaration(Float)

vector_template_collection_declaration(Complex)

UInt vector_UInt_cart2lin(Vector(UInt) coor, Vector(UInt) size);

void vector_UInt_lin2cart_(Vector(UInt) coor, UInt lin, Vector(UInt) size);

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
    Vector(UInt) s; \
    T *v; \
} Array(T);

// alloc

#define array_template_alloc_declaration(T) Array(T) array_##T##_alloc(Vector(UInt) s)

#define array_template_alloc_definition(T) array_template_alloc_declaration(T){ \
    Array(T) _arr;                                                  \
    _arr.s = vector_UInt_dcopy(s);                             \
    _arr.v = (T *)malloc(vector_UInt_product(s) * sizeof(T));  \
    return _arr;                                                    \
}

// read

#define array_template_read_declaration(T) Array(T) array_##T##_read(int fid)

#define array_template_read_definition(T) array_template_read_declaration(T){ \
    UInt n;                                                                   \
    Array(T) _arr;                                                            \
    _arr.s = vector_UInt_read(fid);                                         \
    n = vector_UInt_product(_arr.s);                                        \
    _arr.v = (T *)malloc(n * sizeof(T));                                      \
    read(fid, _arr.v, n * sizeof(T));                                         \
    return _arr;                                                              \
}

#define array_template_write_declaration(T) void array_##T##_write(int fid, Array(T) arr)

#define array_template_write_definition(T) array_template_write_declaration(T){ \
    vector_UInt_write(fid, arr.s);                                            \
    write(fid, arr.v, vector_UInt_product(arr.s) * sizeof(T));                \
}

// free

#define array_template_free_declaration(T) void array_##T##_free_(Array(T) *arr)

#define array_template_free_definition(T) array_template_free_declaration(T){ \
    if(arr->v != NULL) free(arr->v);    \
    arr->v = NULL;                      \
    vector_UInt_free_(&(arr->s));  \
}

// get value

#define array_template_get_declaration(T) T array_##T##_get(Array(T) arr, Vector_UInt coor)

#define array_template_get_definition(T)  array_template_get_declaration(T){ \
    return arr.v[vector_UInt_cart2lin(coor, arr.s)]; \
}

// set value

#define array_template_set_declaration(T) void array_##T##_set_(Array(T) arr, Vector_UInt coor, T val)

#define array_template_set_definition(T) array_template_set_declaration(T){ \
    arr.v[vector_UInt_cart2lin(coor, arr.s)] = val;    \
    return;                                                 \
}

// slice

#define array_template_slice_declaration(T) Vector(T) array_##T##_slice_(Array(T) arr, Vector(UInt) indexs, UInt dim)

#define array_template_slice_definition(T) array_template_slice_declaration(T){ \
    Vector(T) _slice;                                                           \
    UInt i, n;                                                                  \
    n = vector_get(arr.s, dim);                                                 \
    _slice = vector_##T##_alloc(n);                                             \
    for(i=0; i<n; i++){                                                         \
        vector_get(indexs, dim) = i;                                            \
        vector_get(_slice, i) = array_##T##_get(arr, indexs);                   \
    }                                                                           \
    return _slice;                                                              \
}

// map

// reshape

#define array_template_reshape_declaration(T) Array(T) array_##T##_reshape(Array(T) arr, Vector_UInt size)

#define array_template_reshape_definition(T) array_template_reshape_declaration(T){ \
    Array(T) _arr; \
    _arr.s = vector_UInt_dcopy(size); \
    _arr.v = (T *)malloc(vector_UInt_product(size) * sizeof(T)); \
    memcpy(_arr.v, arr.v, vector_UInt_product(size) * sizeof(T));                 \
return _arr;                                                                                    \
}

// macro set

#define array_template_collection_declaration(T) array_template_type_definition(T) \
array_template_alloc_declaration(T); \
array_template_read_declaration(T); \
array_template_write_declaration(T); \
array_template_free_declaration(T); \
array_template_get_declaration(T); \
array_template_set_declaration(T); \
array_template_slice_declaration(T); \
array_template_reshape_declaration(T);

#define array_template_collection_definition(T) array_template_alloc_definition(T) \
array_template_read_definition(T); \
array_template_write_definition(T); \
array_template_free_definition(T) \
array_template_get_definition(T) \
array_template_set_definition(T) \
array_template_slice_definition(T) \
array_template_reshape_definition(T)

array_template_collection_declaration(Int)

array_template_collection_declaration(UInt)

array_template_collection_declaration(Float)

array_template_collection_declaration(Complex)

#endif //SEISTOOLS_C_ARRAY_TEMPLATE_H

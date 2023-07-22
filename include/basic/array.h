//
// Created by chang on 2023/7/22.
//

#ifndef SEISTOOLS_C_ARRAY_H
#define SEISTOOLS_C_ARRAY_H

#include "basic_types.h"

#define ARRAY_CHECK_BOUNDARY

typedef struct seistools_vector_t{
    UInt n;
    size_t e_byte;
    void *data;
} Vector;

Vector vector_zeros(UInt length, size_t size);

void vector_free(Vector *vec);

void *vector_get_addr(Vector vec, UInt index);

void vector_get(void *buf, Vector vec, UInt index);

void vector_set(Vector vec, UInt index, void *buf);

typedef struct seistools_int_vector_t{
    UInt n;
    Int *data;
} IntVec;

IntVec ivec_zeros(UInt length);

IntVec ivec_deepcopy(IntVec ivec);

void ivec_free(IntVec *ivec);

Int ivec_get(IntVec ivec, UInt index);

void ivec_set(IntVec ivec, UInt index, Int value);

typedef struct seistools_float_vector_t{
    UInt n;
    Float *data;
} FloatVec;

FloatVec fvec_zeros(UInt length);

FloatVec fvec_deepcopy(FloatVec fvec);

void fvec_free(FloatVec *fvec);

Float fvec_get(FloatVec fvec, UInt index);

void fvec_set(FloatVec fvec, UInt index, Float value);

typedef struct seistools_matrix_t{
    Int m, n;
    size_t e_byte;
    void *data;
} Matrix;

Matrix matrix_zeros(Int n_row, Int n_column);

void matrix_free(Matrix *mat);

void *matrix_get_addr(Matrix mat, Int row, Int column);

void matrix_get(void *buf, Matrix mat, Int row, Int column);

void matrix_set(void *buf, Matrix mat, Int row, Int column);


#endif //SEISTOOLS_C_ARRAY_H

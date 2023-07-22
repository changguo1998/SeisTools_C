//
// Created by chang on 2023/7/22.
//

#include "array.h"


Vector vector_zeros(UInt length, size_t size){
    Vector _v;
    _v.n = length;
    _v.e_byte = size;
    _v.data = calloc(length, size);
    return _v;
}

void vector_free(Vector *vec){
    if(vec->data != NULL)
        free(vec->data);
    vec->data = NULL;
}

void *vector_get_addr(Vector vec, UInt index){
#ifdef ARRAY_CHECK_BOUNDARY
    if(index >= vec.n){
        errno = ERANGE;
        perror("(vector_get_addr) Out of Range");
    }
#endif
    return vec.data + index * vec.e_byte;
}

void vector_get(void *buf, Vector vec, UInt index){ memcpy(buf, vector_get_addr(vec, index), vec.e_byte); }

void vector_set(Vector vec, UInt index, void *buf){ memcpy(vector_get_addr(vec, index), buf, vec.e_byte); }

IntVec ivec_zeros(UInt length){
    IntVec v;
    v.n = length;
    v.data = (Int *)calloc(length, sizeof(Int));
    return v;
}

IntVec ivec_deepcopy(IntVec ivec){
    IntVec v;
    v = ivec_zeros(ivec.n);
    memccpy(v.data, ivec.data, (int)ivec.n, sizeof(Int));
    return v;
}

Int ivec_get(IntVec ivec, UInt index){
#ifdef ARRAY_CHECK_BOUNDARY
    if(index >= ivec.n){
        errno = ERANGE;
        perror("(ivec_get) Out of Range");
    }
#endif
    return ivec.data[index];
}

void ivec_set(IntVec ivec, UInt index, Int value){
#ifdef ARRAY_CHECK_BOUNDARY
    if(index >= ivec.n){
        errno = ERANGE;
        perror("(ivec_set) Out of Range");
    }
#endif
    ivec.data[index] = value;
}

FloatVec fvec_zeros(UInt length){
    FloatVec v;
    v.n = length;
    v.data = (Float *)calloc(length, sizeof(Float));
    return v;
}

FloatVec fvec_deepcopy(FloatVec fvec){
    FloatVec v;
    v = fvec_zeros(fvec.n);
    memccpy(v.data, fvec.data, (int)fvec.n, sizeof(Float));
    return v;
}

Float fvec_get(FloatVec fvec, UInt index){
#ifdef ARRAY_CHECK_BOUNDARY
    if(index >= fvec.n){
        errno = ERANGE;
        perror("(fvec_get) Out of Range");
    }
#endif
    return fvec.data[index];
}

void fvec_set(FloatVec fvec, UInt index, Float value){
#ifdef ARRAY_CHECK_BOUNDARY
    if(index >= fvec.n){
        errno = ERANGE;
        perror("(ivec_set) Out of Range");
    }
#endif
    fvec.data[index] = value;
}

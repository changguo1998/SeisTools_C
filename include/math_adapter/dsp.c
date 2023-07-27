//
// Created by chang on 2023/7/22.
//

#include "dsp.h"

Float fvec_max(FloatVec fvec, UInt *index){
    UInt i;
    Float val;
    *index = 0;
    val = fvec.data[0];
    for(i = 0; i < fvec.n; i++)
        if(val < fvec.data[i]){
            val = fvec.data[i];
            *index = i;
        }
    return val;
}

Float fvec_min(FloatVec fvec, UInt *index){
    UInt i;
    Float val;
    *index = 0;
    val = fvec.data[0];
    for(i = 0; i < fvec.n; i++)
        if(val > fvec.data[i]){
            val = fvec.data[i];
            *index = i;
        }
    return val;
}

Float fvec_mean(FloatVec fvec){
    Float val;
    UInt i;
    val = 0.0;
    for(i = 0; i < fvec.n; i++) val += fvec.data[i];
    val /= (Float)fvec.n;
    return val;
}

Float fvec_var(FloatVec fvec, Float correct){
    Float _mean, var;
    UInt i;
    _mean = fvec_mean(fvec);
    var = 0.0;
    for(i = 0; i < fvec.n; i++) var += (fvec.data[i] - _mean) * (fvec.data[i] - _mean);
    var /= (Float)fvec.n - correct;
    return var;
}

Float fvec_std(FloatVec fvec, Float correct){
    Float _var;
    _var = fvec_var(fvec, correct);
    return (Float)sqrtl(_var);
}

void fvec_sort(FloatVec fvec_sorted, FloatVec fvec, IntVec perm){
    UInt i, j;
    Int ibuff, *id_buff;
    Float fbuff;
    memcpy(fvec_sorted.data, fvec.data, fvec.n * sizeof(Float));
    id_buff = (Int *)calloc(fvec.n, sizeof(Int));
    for(i = 0; i < fvec.n; i++) id_buff[i] = i;
    for(i = 0; i < fvec.n; i++)
        for(j = i + 1; j < fvec.n; j++)
            if(fvec_sorted.data[i] > fvec_sorted.data[j]){
                fbuff = fvec_sorted.data[i];
                fvec_sorted.data[i] = fvec_sorted.data[j];
                fvec_sorted.data[j] = fbuff;
                ibuff = id_buff[i];
                id_buff[i] = id_buff[j];
                id_buff[j] = ibuff;
            }
    for(i = 0; i < fvec.n; i++) perm.data[id_buff[i]] = i;
    free(id_buff);
}

Float fvec_dot(FloatVec fv1, FloatVec fv2){
    UInt i;
    Float buff;
#ifdef ARRAY_CHECK_BOUNDARY
    if(fv1.n != fv2.n){
        errno = ERANGE;
        perror("(fvec_dot) Dimension mismatch");
    }
#endif
    buff = 0.0;
    for(i = 0; i < fv1.n; i++) buff += fv1.data[i] * fv2.data[i];
    return buff;
}

void fvec_cross(FloatVec result, FloatVec fv1, FloatVec fv2){
#ifdef ARRAY_CHECK_BOUNDARY
    if(fv1.n != fv2.n){
        errno = ERANGE;
        perror("(fvec_dot) Dimension mismatch");
    }
    if(fv1.n != 3){
        errno = ERANGE;
        perror("(fvec_dot) Dimension must be 3");
    }
#endif
    fvec_set(result, 0, fv1.data[1] * fv2.data[2] - fv1.data[2] * fv2.data[1]);
    fvec_set(result, 1, fv1.data[2] * fv2.data[0] - fv1.data[0] * fv2.data[2]);
    fvec_set(result, 2, fv1.data[0] * fv2.data[1] - fv1.data[1] * fv2.data[0]);
}

void fmat_matrix_product(FloatMat result, FloatMat A, FloatMat B){
    UInt i, j, k;
#ifdef ARRAY_CHECK_BOUNDARY
    if((result.nrow != A.nrow) || (result.ncol != B.ncol) || (A.ncol != B.nrow)){
        errno = ERANGE;
        perror("(fvec_dot) Dimension mismatch");
    }
#endif
    for(i = 0; i < result.nrow * result.ncol; i++) result.data[i] = 0.0;
    for(i = 0; i < result.nrow; i++)
        for(j = 0; j < result.ncol; j++)
            for(k = 0; k < A.ncol; k++)
                result.data[i + j * result.nrow] += A.data[i + k * A.nrow] * B.data[k + j * B.nrow];
}

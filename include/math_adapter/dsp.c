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

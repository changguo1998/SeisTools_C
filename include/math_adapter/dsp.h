//
// Created by chang on 2023/7/22.
//

#ifndef SEISTOOLS_C_DSP_H
#define SEISTOOLS_C_DSP_H

//#include "ftw.h"
#include "../basic/array.h"

Float fvec_max(FloatVec fvec, UInt *index);

Float fvec_min(FloatVec fvec, UInt *index);

Float fvec_mean(FloatVec fvec);

Float fvec_var(FloatVec fvec, Float correct);

Float fvec_std(FloatVec fvec, Float correct);

void fvec_sort(FloatVec fvec_sorted, FloatVec fvec, IntVec perm);

void fvec_detrend(FloatVec fvec);

void fvec_taper(FloatVec fvec, FloatVec weight);

typedef struct{
    Float k;
    void *b;
    void *a;
} Filter;

void fvec_filtfilt(FloatVec fvec, Filter v);

#endif //SEISTOOLS_C_DSP_H

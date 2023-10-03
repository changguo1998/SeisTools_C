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

#ifndef SEISTOOLS_C_DSP_H
#define SEISTOOLS_C_DSP_H

//#include "ftw.h"
#include "../basic/array_template.h"

Float fvec_max(FloatVec fvec, UInt *index);

Float fvec_min(FloatVec fvec, UInt *index);

Float fvec_mean(FloatVec fvec);

Float fvec_var(FloatVec fvec, Float correct);

Float fvec_std(FloatVec fvec, Float correct);

void fvec_sort(FloatVec fvec_sorted, FloatVec fvec, IntVec perm);

void fvec_detrend(FloatVec fvec);

void fvec_taper(FloatVec fvec, FloatVec weight);

void fvec_xcorr(FloatVec xc, FloatVec fv1, FloatVec fv2, Int shift1, Int shift2);

void fvec_conv(FloatVec cv, FloatVec fv1, FloatVec fv2);

void fvec_xcorr_fft(FloatVec xc, FloatVec fv1, FloatVec fv2);

void fvec_conv_fft(FloatVec cv, FloatVec fv1, FloatVec fv2);

Float fvec_dot(FloatVec fv1, FloatVec fv2);

void fvec_cross(FloatVec result, FloatVec fv1, FloatVec fv2);

typedef struct{
    Float k;
    void *b;
    void *a;
} Filter;

void fvec_filtfilt(FloatVec fvec, Filter v);

void fmat_matrix_product(FloatMat result, FloatMat A, FloatMat B);

#endif //SEISTOOLS_C_DSP_H

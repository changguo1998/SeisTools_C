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

#include "../include/basic/array_template.h"
#include "../include/math_adapter/dsp.h"
#include <time.h>

#define VECTOR_LENGTH 5

void printmat(FloatMat fm){
    UInt i, j;
    for(i = 0; i < fm.nrow; i++){
        for(j = 0; j < fm.ncol; j++){
            printf("%f ", fmat_get(fm, i, j));
        }
        printf("\n");
    }
}

int main(void){
    FloatVec fu, fv, fw;
    FloatMat fm_A, fm_B, fm_C;
    IntVec iv;
    UInt uibuff;
    Int i;
    srand((unsigned)time(NULL));
    fv = fvec_zeros(VECTOR_LENGTH);
    for(i = 0; i < fv.n; i++) fvec_set(fv, i, roundl((Float)rand() / ((Float)RAND_MAX) * 100.0) * 0.01);
    fw = fvec_deepcopy(fv);

    printf("fv:\n");
    for(i = 0; i < fv.n; i++) printf("%.2f ", fvec_get(fv, i));
    printf("\n");
    printf("fw:\n");
    for(i = 0; i < fv.n; i++) printf("%.2f ", fvec_get(fw, i));
    printf("\n");

    printf("mean fv: %f\nmax fv: %.2f\nmin fv: %.2f\nvar fv: %f\nstd fv: %f\n", fvec_mean(fv), fvec_max(fv, &uibuff),
           fvec_min(fv, &uibuff), fvec_var(fv, 0.0), fvec_std(fv, 0.0));
    iv = ivec_zeros(fv.n);
    fvec_sort(fw, fv, iv);
    printf("fv range:\n");
    for(i = 0; i < fv.n; i++) printf("%.2f\t", fvec_get(fv, i));
    printf("\n");
    for(i = 0; i < fv.n; i++) printf("%4ld\t", ivec_get(iv, i));
    printf("\n");
    printf("sorted:\n");
    for(i = 0; i < fv.n; i++) printf("%.2f ", fvec_get(fw, i));
    printf("\n");
    fvec_free(&fv);
    fvec_free(&fw);
    ivec_free(&iv);

    fu = fvec_zeros(3);
    fv = fvec_zeros(3);
    fw = fvec_zeros(3);

    fvec_set(fu, 0, 1.0);
    fvec_set(fu, 1, 0.0);
    fvec_set(fu, 2, 0.0);
    fvec_set(fv, 0, 1.0);
    fvec_set(fv, 1, 1.0);
    fvec_set(fv, 2, 0.0);
    fvec_cross(fw, fu, fv);
    printf("fu:");
    for(i = 0; i < 3; i++) printf(" %f", fvec_get(fu, i));
    printf("\n");
    printf("fv:");
    for(i = 0; i < 3; i++) printf(" %f", fvec_get(fv, i));
    printf("\n");
    printf("fu . fv: %f\n", fvec_dot(fu, fv));
    printf("fu x fv:");
    for(i = 0; i < 3; i++) printf(" %f", fvec_get(fw, i));
    printf("\n");

    fvec_free(&fu);
    fvec_free(&fv);
    fvec_free(&fw);

    fm_A = fmat_zeros(3, 2);
    fm_B = fmat_zeros(2, 1);
    fm_C = fmat_zeros(3, 1);
    fmat_set(fm_A, 0, 0, 1.0);
    fmat_set(fm_A, 0, 1, 2.0);
    fmat_set(fm_A, 1, 0, 3.0);
    fmat_set(fm_A, 1, 1, 4.0);
    fmat_set(fm_A, 2, 0, 5.0);
    fmat_set(fm_A, 2, 1, 6.0);
    fmat_set(fm_B, 0, 0, 1.0);
    fmat_set(fm_B, 1, 0, 0.5);
    fmat_matrix_product(fm_C, fm_A, fm_B);
    printf("A:\n");
    printmat(fm_A);
    printf("B:\n");
    printmat(fm_B);
    printf("C:\n");
    printmat(fm_C);
    fmat_free(&fm_A);
    fmat_free(&fm_B);
    fmat_free(&fm_C);
    return 0;
}

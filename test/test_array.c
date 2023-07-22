//
// Created by chang on 2023/7/23.
//

#include "../include/basic/array.h"
#include "../include/math_adapter/dsp.h"
#include <time.h>

#define VECTOR_LENGTH 5

int main(void){
    FloatVec fv, fw;
    IntVec iv;
    UInt uibuff;
    Int i;
    srand(time(NULL));
    fv = fvec_zeros(VECTOR_LENGTH);
    for(i = 0; i < fv.n; i++) fvec_set(fv, i, roundl(rand() / ((Float)RAND_MAX) * 100.0) * 0.01);
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
    return 0;
}
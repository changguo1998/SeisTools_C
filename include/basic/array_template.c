//
// Created by chang on 2023/7/22.
//

#include "array_template.h"


array_inner_ivec_t array_inner_ivec_alloc(uint64 n){
    array_inner_ivec_t iv;
    iv.n = n;
    iv.v = (uint64 *)malloc(n * sizeof(uint64));
    return iv;
}

array_inner_ivec_t array_inner_ivec_dcopy(array_inner_ivec_t iv){
    array_inner_ivec_t iw;
    iw.n = iv.n;
    iw.v = (uint64 *)malloc(iv.n * sizeof(uint64));
    memcpy(iw.v, iv.v, iw.n * sizeof(uint64));
    return iw;
}

void array_inner_ivec_free_(array_inner_ivec_t *iv){
    if(iv->v != NULL) free(iv->v);
    iv->v = NULL;
    iv->n = 0;
}

uint64 array_inner_ivec_product(array_inner_ivec_t iv){
    uint64 p, i;
    p = 1;
    for(i = 0; i < iv.n; i += 1) p *= array_m_vector_get(iv, i);
    return p;
}

uint64 array_inner_ivec_cart2lin(array_inner_ivec_t coor, array_inner_ivec_t size){
    uint64 index;
    int64 i;
#ifdef ARRAY_CHECK_BOUNDARY
    for(i = 0; i < coor.n; i++)
        if(array_m_vector_get(coor, i) >= array_m_vector_get(size, i)){
            printf("Out of index\n");
            errno = ERANGE;
            exit(ERANGE);
        }
#endif
    index = array_m_vector_get(coor, coor.n - 1);
    for(i = (int64)coor.n - 2; i >= 0; i -= 1){
        index *= array_m_vector_get(size, i);
        index += array_m_vector_get(coor, i);
    }
    return index;
}

void array_inner_ivec_lin2cart_(array_inner_ivec_t coor, uint64 lin, array_inner_ivec_t size){
    uint64 i;
    for(i = 0; i < coor.n; i++){
        array_m_vector_get(coor, i) = lin % array_m_vector_get(size, i);
        lin /= array_m_vector_get(size, i);
    }
}

array_template_collection_definition(int)

array_template_collection_definition(int64)

array_template_collection_definition(float)

array_template_collection_definition(double)
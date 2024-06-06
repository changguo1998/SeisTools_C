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

#include "array_template.h"

vector_template_collection_definition(Int)

vector_template_collection_definition(UInt)

vector_template_collection_definition(Float)

vector_template_collection_definition(Complex)


UInt vector_UInt_cart2lin(Vector(UInt) coor, Vector(UInt) size){
    UInt index;
    Int i;
#ifdef ARRAY_CHECK_BOUNDARY
    for(i = 0; i < coor.n; i++)
        if(vector_get(coor, i) >= vector_get(size, i)){
            printf("Out of index\n");
            errno = ERANGE;
            exit(ERANGE);
        }
#endif
    index = vector_get(coor, coor.n - 1);
    for(i = (Int)coor.n - 2; i >= 0; i -= 1){
        index *= vector_get(size, i);
        index += vector_get(coor, i);
    }
    return index;
}

void vector_UInt_lin2cart_(Vector(UInt) coor, UInt lin, Vector(UInt) size){
    UInt i;
    for(i = 0; i < coor.n; i++){
        vector_get(coor, i) = lin % vector_get(size, i);
        lin /= vector_get(size, i);
    }
}

array_template_collection_definition(Int)

array_template_collection_definition(UInt)

array_template_collection_definition(Float)

array_template_collection_definition(Complex)

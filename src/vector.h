/*
    = VECTOR
    = Author: Bartosz Kania
    = Description: Simple Vector for educational purposes. No stability guaranted!!!

    = TODO: Find out why I can't pushback undefined values directly through the function
*/
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// LIMIT = Initial size of vector
#define LIMIT 10

typedef struct Vector{
    void* items;
    size_t elem_size;
    size_t limit;
    size_t current;
} Vector;

void VECTOR_INIT(Vector* v, const size_t elem_size);
void VECTOR_RESIZE(Vector *v, size_t limit); 

void VECTOR_PUSHBACK(Vector *v, void* data); 

void VECTOR_FREE(Vector *v);

void VECTOR_SET(Vector *v, void* data, size_t index);

void* VECTOR_GET(Vector *v, size_t index);

void VECTOR_DELETE(Vector *v, size_t index);

#endif

#include "vector.h"

void VECTOR_INIT(Vector* v, const size_t elem_size) {
    v->limit = LIMIT;
    v->current = 0;
    v->elem_size = elem_size;

    v->items = (void*)malloc(LIMIT * elem_size);
}


void VECTOR_RESIZE(Vector *v, size_t limit) {
    assert(v != NULL && "Empty Vector passed as an argument");

    v->items = (void*)realloc(v->items, v->elem_size * limit);
    v->limit = limit;
}

void VECTOR_PUSHBACK(Vector *v, void* data) {
    // We check if amount of objects in vector aren't larger than limit. If yes then we resize it.
    if (v->current >= v->limit)
        VECTOR_RESIZE(v, v->current + (v->current / 2));

    assert(v->current >= 0 && "Index out of range");

    memcpy(&(v->items[v->current * v->elem_size]), data, v->elem_size);

    v->current++;
}


void VECTOR_FREE(Vector *v) {
    assert(v != NULL && "Empty Vector passed as an argument");

    for(size_t i = 0; i < v->current; i++) {
        // We set elements memory to 0 for extra safety (Not sure if it's correct)
        memset(VECTOR_GET(v, i), 0, v->elem_size);
    }

    free(v->items);
    v->items = NULL;
}

void VECTOR_SET(Vector *v, void* data, size_t index) {
    assert(index >= 0 && "Index out of range");
    assert(index <= v->current - 1 && "Index out of range");

    memset(VECTOR_GET(v, index), 0, v->elem_size);

    memcpy(VECTOR_GET(v, index), data, v->elem_size);
}

void* VECTOR_GET(Vector *v, size_t index) {
    assert(index <= v->current - 1 && "Index out of range");
    assert(index >= 0 && "Index out of range");

    return &(v->items[index * v->elem_size]);
}

void VECTOR_DELETE(Vector *v, size_t index) {
    assert(index >= 0 && "Index out of range");
    assert(index <= v->current - 1 && "Index out of range");

    memset(VECTOR_GET(v, index), 0, v->elem_size);

    // After deleting an element, we move everything one index down
    for(size_t i = index; i < (v->current - 1); i++) {
        memcpy(VECTOR_GET(v, i), VECTOR_GET(v, i + 1), v->elem_size);
        memset(VECTOR_GET(v, i + 1), 0, v->elem_size);
    }

    v->current -= 1;

    if (v->current > 0 && v->current <= (v->limit / 2))
        VECTOR_RESIZE(v, v->limit - (v->current / 2));

}


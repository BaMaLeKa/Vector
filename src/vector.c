#include "vector.h"

void VECTOR_INIT(Vector* v, const size_t elem_size) {
    v->limit = LIMIT;
    v->current = 0;
    v->elem_size = elem_size;

    v->items = (void*)malloc(LIMIT * elem_size);
}

// TODO: Zmienić reakcje na nieudane resizowanie
void VECTOR_RESIZE(Vector *v, size_t limit) {
    if (v != NULL) {
        void* items = (void *)realloc(v->items, v->elem_size * limit);
        if (items != NULL) {
            v->items = items;
            v->limit = limit;
        }
    }
    else
        fprintf(stdout, "Zmienianie wielkosci vektora nie powiodlo sie\n");
}

void VECTOR_PUSHBACK(Vector *v, void* data) {
    // Sprawdzamy czy ilość elementów w vektorze nie jest większa niż jej limit i w razie czego zmieniamy jej rozmiar.
    if (v->current >= v->limit)
        VECTOR_RESIZE(v, v->current + (v->current / 2));

    assert(v->current >= 0);

    memcpy(&(v->items[v->current * v->elem_size]), data, v->elem_size);

    v->current++;
}


void VECTOR_FREE(Vector *v) {
    if (v != NULL) {

        for(size_t i = 0; i < v->current; i++) {
            // Zerujemy wartości przetrzymywanych danych by nic nie zostało
            memset(VECTOR_GET(v, i), 0, v->elem_size);
        }

        free(v->items);
        v->items = NULL;
        fprintf(stdout, "Vector poprawnie zniszczony \n");
    }
    else
        fprintf(stdout, "Vector juz jest pusty\n");
}

void VECTOR_SET(Vector *v, void* data, size_t index) {
    assert(index >= 0);
    assert(index <= v->current - 1);

    memset(VECTOR_GET(v, index), 0, v->elem_size);

    memcpy(VECTOR_GET(v, index), data, v->elem_size);
}

void* VECTOR_GET(Vector *v, size_t index) {
    assert(index <= v->current - 1);
    assert(index >= 0);

    return &(v->items[index * v->elem_size]);
}

void VECTOR_DELETE(Vector *v, size_t index) {
    assert(index >= 0);
    assert(index <= v->current - 1);

    memset(VECTOR_GET(v, index), 0, v->elem_size);

    //Po usunięciu elementu, przemieszczamy wszystko przed nim o jedno miejsce do tyłu.
    for(size_t i = index; i < (v->current - 1); i++) {
        memcpy(VECTOR_GET(v, i), VECTOR_GET(v, i + 1), v->elem_size);
        memset(VECTOR_GET(v, i + 1), 0, v->elem_size);
    }

    v->current -= 1;

    if (v->current > 0 && v->current <= (v->limit / 2))
        VECTOR_RESIZE(v, v->limit - (v->current / 2));

}


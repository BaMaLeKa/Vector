/*
    = VECTOR
    = Autor: Bartosz Kania
    = Opis: Prosty Vector do użytku własnego, może kiedyś go poprawie, 
    = ale zadowala mnie jego obecna forma
    = Inspirowany Vectorem z https://aticleworld.com/implement-vector-in-c/
*/
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

#define LIMIT 10

typedef struct {
    void** items;
    size_t limit;
    size_t current;
} Vector;

void VECTOR_INIT(Vector* v) {
    v->limit = LIMIT;
    v->current = 0;
    v->items = (void**)calloc(LIMIT, sizeof(void*));
}

// Resizowanie VECTORA jest statyczne ponieważ chce, aby VECTOR robił to za użytkownika.
// Więc nie pozwalam użytkownikowi nawet tykać tej funkcji.
static void VECTOR_RESIZE(Vector *v, size_t limit) {
    if (v != NULL) {
        void** items = (void **)realloc(v->items, sizeof(void*) * limit);
        if (items != NULL) {
            v->items = items;
            v->limit = limit;
        }
    }
    else
        fprintf(stdout, "Cos nie pyklo z resizowaniem Vectora\n");
}

void VECTOR_PUSHBACK(Vector *v, void* data) {
    if (v->current >= v->limit)
        VECTOR_RESIZE(v, v->current + (v->current / 2));

    v->items[v->current] = data;
    v->current += 1;
}

void VECTOR_FREE(Vector *v) {
    if (v != NULL) {
        free(v->items);
        //Nie wiem szczerze po co to tak zrobiłem, ale dla pewności ustawiam wszystko co mogło zostać na NULL
        for(size_t i = 0; i < v->current; i++)
            v->items[i] = NULL;
        v->items = NULL;
    }
    else
        fprintf(stdout, "Vector juz jest pusty\n");
}

void VECTOR_SET(Vector *v, void* data, int index) {
    if (index < 0 || index > v->current)
        return;

    v->items[index] = data;
}

void* VECTOR_GET(Vector *v, int index) {
    if (index < 0 || index > v->current)
        return;

    return v->items[index];
}

void VECTOR_DELETE(Vector *v, int index) {
    if (index < 0 || index > v->current)
        return;

    v->items[index] = NULL;

    //Po usunięciu elementu, przemieszczamy wszystko przed nim o jedno miejsce do tyłu.
    for(size_t i = index; i < (v->current - 1); i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->current -= 1;

    if (v->current > 0 && v->current <= (v->limit / 2))
        VECTOR_RESIZE(v, v->limit - (v->current / 2));
}

#endif
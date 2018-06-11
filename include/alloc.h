#pragma once

#include <stdbool.h>
#include <stdlib.h>


typedef void (*mark_func)(void*, int);

typedef struct alloc
{
    int current_mark;
    void* ptr;
    mark_func mark;
} alloc;

alloc* alloc_new();

bool alloc_init(alloc* a, size_t size, mark_func mark);
void alloc_mark(alloc* a, int new_mark);
void alloc_destroy(alloc* a);

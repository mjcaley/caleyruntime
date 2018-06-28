#pragma once

#include <stddef.h>


extern int gc_mark;

typedef struct Type
{
    void (*traverse)(void*, void (*f)(void*));
    size_t size;
    char* name;
} Type;


void gc_init(const Type* type, void* ptr);
void* gc_malloc(const Type* type);
void gc_free(void* ptr);

void gc_mark_ptr(void* ptr);

int gc_get_mark(void* ptr);

void gc_mark();
void gc_sweep();
void gc_collect();
void traverse(void* ptr, void (*f)(void*));

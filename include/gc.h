#pragma once

#include <stddef.h>
#include <stdbool.h>


extern int mark;

typedef struct Type
{
    void (*traverse)(void*, void (*f)(void*));
    size_t size;
    char* name;
} Type;

typedef struct GCObject
{
    const Type* type;
    int mark;
} GCObject;


void gc_init(const Type* type, GCObject* ptr);
void* gc_malloc(const Type* type);
void gc_free(void* ptr);

void gc_mark_ptr(void* ptr);

int gc_get_mark(void* ptr);

void gc_mark();
void gc_sweep();
void gc_collect();
void traverse(void* ptr, void (*f)(void*));

bool gc_is_not_marked(void* ptr);

#include <stdlib.h>

#include "gc.h"


int gc_mark = 0;


static inline int* gc_get_mark_ptr(void* ptr)
{
    return (int*)(ptr - sizeof(int));
}

static inline Type** gc_get_type_ptr(void* ptr)
{
    return (Type**)(ptr - sizeof(int) - sizeof(Type*));
}

void gc_init(const Type* type, void* ptr)
{
    *gc_get_mark_ptr(ptr) = gc_mark;
    *gc_get_type_ptr(ptr) = type;
}

void* gc_malloc(const Type* type)
{
    void* alloc = malloc(sizeof(Type*) + sizeof(int) + type->size);
    void* ptr = (alloc + sizeof(Type*) + sizeof(int));
    gc_init(type, ptr);
    return ptr;
}

void gc_free(void* ptr)
{
    free(ptr - sizeof(int) - sizeof(Type*));
}

void gc_mark_ptr(void* ptr)
{
    *gc_get_mark_ptr(ptr) = gc_mark;
}


int gc_get_mark(void* ptr)
{
    return *gc_get_mark_ptr(ptr);
}


void traverse(void* ptr, void (*f)(void*))
{
    Type* temp = *gc_get_type_ptr(ptr);
    temp->traverse(ptr, f);
}

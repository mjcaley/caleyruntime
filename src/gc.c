#include <stdlib.h>

#include "gc.h"


int gc_mark = 0;


void gc_init(const Type* type, void* ptr)
{
    *(int*)(ptr - sizeof(int)) = gc_mark;
    *(Type**)(ptr - sizeof(int) - sizeof(Type*)) = type;
}

void* gc_malloc(const Type* type)
{
    void* ptr = malloc(sizeof(Type*) + sizeof(int) + type->size);
    gc_init(type, ptr);
    return (char*)ptr + sizeof(Type*) + sizeof(int);
}

void gc_free(void* ptr)
{
    free(ptr - sizeof(int) - sizeof(Type*));
}

void gc_mark_ptr(void* ptr)
{
    *(int*)(ptr - sizeof(int)) = gc_mark;
}


int gc_get_mark(void* ptr)
{
    return *(int*)(ptr - sizeof(int));
}


void traverse(void* ptr, void (*f)(void*))
{
    Type* temp = (Type*)((char*)ptr - sizeof(int) - sizeof(Type*));
    temp->traverse(ptr, f);
}


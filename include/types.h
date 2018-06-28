#pragma once

#include <stddef.h>
#include <stdlib.h>


void traverse_int(void*, void(*f)(void*)) {}


typedef struct Type
{
    void (*traverse)(void*, void (*f)(void*));
    size_t size;
    char* name;
} Type;

const Type types[] = {
    [0] = { &traverse_int, sizeof(int), "int" }
};


void* gc_malloc(Type* type)
{
    void* ptr = malloc(sizeof(Type*) + sizeof(int) + type->size);
    return (char*)ptr + sizeof(Type*) + sizeof(int);
}



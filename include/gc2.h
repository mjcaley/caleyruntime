#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "typeinfo.h"


extern int mark;

typedef struct Header
{
    const TypeInfo* type;
    int mark;
    size_t length;
} Header;

void* gc_malloc2(const TypeInfo* type);
void* gc_malloc_array(const TypeInfo* type, size_t length);
void gc_free2(void* ptr);

void gc_mark_ptr2(void* ptr);

void traverse2(void* ptr, void (*f)(void*));

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

void* gc_malloc(const TypeInfo* type);
void* gc_malloc_array(const TypeInfo* type, size_t length);
void gc_free(void* ptr);

const Header *const gc_get_header(void* ptr);

void gc_mark_ptr(void* ptr);

void traverse(void* ptr, void (*f)(void*));

void gc_mark();
void gc_sweep();
void gc_collect();

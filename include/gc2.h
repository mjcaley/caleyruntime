#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "typeinfo.h"


extern int mark;

typedef struct GCObject2
{
    const TypeInfo* type;
    int mark;
} GCObject2;

void gc_init2(const TypeInfo* type, GCObject2* ptr);
void* gc_malloc2(const TypeInfo* type);
void gc_free2(void* ptr);

void gc_mark_ptr2(void* ptr);

void traverse2(void* ptr, void (*f)(void*));

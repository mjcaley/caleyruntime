#pragma once

#include <stddef.h>
#include <stdbool.h>


extern int mark;

typedef struct Type2
{
    size_t size;
    char* name;
    size_t offset_len;
    size_t offsets[];
} Type2;

typedef struct GCObject2
{
    const Type2* type;
    int mark;
} GCObject2;

void gc_init2(const Type2* type, GCObject2* ptr);
void* gc_malloc2(const Type2* type);
void gc_free2(void* ptr);

void gc_mark_ptr2(void* ptr);

void traverse2(void* ptr, void (*f)(void*));

void gc_mark2(GCList* self);
void gc_sweep2(GCList* self);
void gc_collect(GCList* self);

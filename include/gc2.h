#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "typeinfo.h"


extern int mark;


typedef struct
{
    const TypeInfo* type;
    size_t length;
} TypeTag;

typedef struct
{
    int mark;
    TypeTag type_tag;
} GCHeader;


// init_header
void* init_type_tag(TypeTag* type_tag, const TypeInfo* type, size_t length);


// stack_alloc
#ifndef alloc_stack
#define alloc_stack(T) init_type_tag( \
  (char[sizeof(TypeTag) + (T.size)]){0}, T, 1)
#endif
// stack_alloc_array
#ifndef alloc_stack_array
#define alloc_stack_array(T, size) header_init( \
  (char[sizeof(Header) + sizeof(T)]){0}, T, size)
#endif

// init_gc_header
void init_gc_header(GCHeader* self, TypeTag type_tag);
// heap_alloc_array
void* alloc_heap_array(const TypeInfo* type_info, size_t num);
// heap_alloc
void* alloc_heap(const TypeInfo* type_info);
// heap_free
void alloc_free(void* ptr);


// Debugging functions
void print_gcheader(void* ptr);

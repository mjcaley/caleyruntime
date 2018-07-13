#include "gc2.h"


int mark = 0;


// init_header
void init_type_tag(TypeTag* type_tag, const TypeInfo* type, size_t length)
{
    type_tag->type = type;
    type_tag->length = length;
}

// stack_alloc
#define alloc_stack(T) type_tag_init( \
  (char[sizeof(TypeTag) + sizeof(T)]){0}, T, 0)
// stack_alloc_array
#define alloc_stack_array(T, size) header_init( \
  (char[sizeof(Header) + sizeof(T)]){0}, T, size)

// init_gc_header
void init_gc_header(GCHeader* self, TypeTag type_tag)
{
    self->mark = mark;
    self->type_tag = type_tag;
}
// heap_alloc_array
void* alloc_heap_array(const TypeInfo* type_info, size_t num)
{
    // void* alloc = malloc(sizeof(GCHeader) + (sizeof(type_info->size) * num));
    // memset(alloc, 0, sizeof(GCHeader) + (sizeof(type_info->size) * num));
    void* alloc = calloc(1, sizeof(GCHeader) + (sizeof(type_info->size) * num));

    GCHeader* header = alloc;
    // TypeTag tag = { .type=type_info, .length=num };
    type_tag_init(header->type_tag, type_info, num);
    init_gc_header(header, tag);

    void* ptr = (char*)alloc + sizeof(GCHeader);

    return ptr;
}
// heap_alloc
void* alloc_heap(const TypeInfo* type_info)
{
    return alloc_heap_array(type_info, 1);
}
// heap_free
void alloc_free(void* ptr)
{
    free((char*)ptr - sizeof(GCHeader));
}


#include <stdio.h>

void print_gcheader(void* ptr)
{
    GCHeader* header = (GCHeader*)((char*)ptr - sizeof(GCHeader));
    printf("[%p] Name: %s, Size: %i, Length: %i, Mark: %i\n", header, header->type_tag.type->name, header->type_tag.type->size, header->type_tag.length, header->mark);
}

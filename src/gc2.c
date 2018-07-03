#include <stdlib.h>

#include "typeinfo.h"
#include "gc2.h"
#include "gc_list.h"


static void gc_init2(Header* alloc, const TypeInfo* type, size_t length)
{
    alloc->type = type;
    alloc->mark = mark;
    alloc->length = length;
}


void* gc_malloc2(const TypeInfo* type)
{
    void* alloc = calloc(1, sizeof(Header) + type->size);
    gc_init2(alloc, type, 0);
    void* ptr = alloc + sizeof(Header);

    return ptr;
}


void* gc_malloc_array(const TypeInfo* type, size_t length)
{
    void* alloc = calloc(1, sizeof(Header) + type->size * length);
    gc_init2(alloc, type, length);
    void* ptr = alloc + sizeof(Header);

    return ptr;
}


void gc_free2(void* ptr)
{
    void* alloc = ptr - sizeof(Header);
    free(alloc);
}


void gc_mark_ptr2(void* ptr)
{
    if (!ptr) { return; }

    Header* obj = ptr - sizeof(Header);
    if (obj->mark != mark)
    {
        obj->mark = mark;
        traverse2(ptr, gc_mark_ptr2);
    }
}


int gc_get_mark2(void* ptr)
{
    Header* obj = ptr - sizeof(Header);
    return obj->mark;
}


void traverse2(void* ptr, void (*f)(void*))
{
    Header* obj = (Header*)((char*)ptr - sizeof(Header));
    for (size_t i = 0; i < obj->type->offset_len; ++i)
    {
        size_t offset = obj->type->offsets[i];
        void* member_ptr = *((void**)(ptr + offset));
        f(member_ptr);
    }
}

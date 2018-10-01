#include <stdlib.h>

#include "typeinfo.h"
#include "gc.h"
#include "gc_list.h"


int mark = 0;

static void gc_init(Header* alloc, const TypeInfo* type, size_t length)
{
    alloc->type = type;
    alloc->mark = mark;
    alloc->length = length;
}


void* gc_malloc(const TypeInfo* type)
{
    void* alloc = calloc(1, sizeof(Header) + type->size);
    gc_init(alloc, type, 0);
    void* ptr = alloc + sizeof(Header);

    return ptr;
}


void* gc_malloc_array(const TypeInfo* type, size_t length)
{
    void* alloc = calloc(1, sizeof(Header) + type->size * length);
    gc_init(alloc, type, length);
    void* ptr = alloc + sizeof(Header);

    return ptr;
}


void gc_free(void* ptr)
{
    void* alloc = ptr - sizeof(Header);
    free(alloc);
}


const Header *const gc_get_header(void* ptr)
{
    Header* obj = ptr - sizeof(Header);
    return obj;
}


void gc_mark_ptr(void* ptr)
{
    if (!ptr) { return; }

    Header* obj = ptr - sizeof(Header);
    if (obj->mark != mark)
    {
        obj->mark = mark;
        traverse(ptr, gc_mark_ptr);
    }
}


int gc_get_mark(void* ptr)
{
    Header* obj = ptr - sizeof(Header);
    return obj->mark;
}


void traverse(void* ptr, void (*f)(void*))
{
    Header* obj = (Header*)((char*)ptr - sizeof(Header));
    for (size_t i = 0; i < obj->type->offset_len; ++i)
    {
        size_t offset = obj->type->offsets[i];
        void* member_ptr = *((void**)(ptr + offset));
        f(member_ptr);
    }
}


void gc_mark()
{
    ++mark;

}


void gc_sweep()
{
    
}


void gc_collect()
{
    gc_mark();
    gc_sweep();
}

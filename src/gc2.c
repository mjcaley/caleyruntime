#include <stdlib.h>

#include "typeinfo.h"
#include "gc2.h"
#include "gc_list.h"


void gc_init2(const TypeInfo* type, GCObject2* ptr)
{
    ptr->type = type;
    ptr->mark = mark;
}


void* gc_malloc2(const TypeInfo* type)
{
    void* alloc = malloc(sizeof(GCObject2) + type->size);
    gc_init2(type, alloc);
    void* ptr = alloc + sizeof(GCObject2);
    return ptr;
}


void gc_free2(void* ptr)
{
    void* alloc = ptr - sizeof(GCObject2);
    free(alloc);
}


void gc_mark_ptr2(void* ptr)
{
    if (!ptr) { return; }

    GCObject2* obj = ptr - sizeof(GCObject2);
    if (obj->mark != mark)
    {
        obj->mark = mark;
        traverse2(ptr, gc_mark_ptr2);
    }
}


int gc_get_mark2(void* ptr)
{
    GCObject2* obj = ptr - sizeof(GCObject2);
    return obj->mark;
}


void traverse2(void* ptr, void (*f)(void*))
{
    GCObject2* obj = (GCObject2*)((char*)ptr - sizeof(GCObject2));
    for (size_t i = 0; i < obj->type->offset_len; ++i)
    {
        size_t offset = obj->type->offsets[i];
        void* member_ptr = *((void**)(ptr + offset));
        f(member_ptr);
    }
}

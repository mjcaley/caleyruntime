#include <stdlib.h>

#include "gc.h"


int mark = 0;


void gc_init(const Type* type, GCObject* ptr)
{
    ptr->type = type;
    ptr->mark = mark;
}


void* gc_malloc(const Type* type)
{
    void* alloc = malloc(sizeof(GCObject) + type->size);
    gc_init(type, alloc);
    void* ptr = alloc + sizeof(GCObject);
    return ptr;
}


void gc_free(void* ptr)
{
    free(ptr - sizeof(GCObject));
}


void gc_mark_ptr(void* ptr)
{
    GCObject* obj = ptr - sizeof(GCObject);
    obj->mark = mark;
}


int gc_get_mark(void* ptr)
{
    GCObject* obj = ptr - sizeof(GCObject);
    return obj->mark;
}


void gc_mark()
{

}


void gc_sweep()
{

}


void gc_collect()
{
    ++mark;
    gc_mark();
    gc_sweep();
}


void traverse(void* ptr, void (*f)(void*))
{
    GCObject* obj = (GCObject*)(ptr - sizeof(GCObject));
    obj->type->traverse(ptr, f);
}

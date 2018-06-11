#include "alloc.h"


alloc* alloc_new()
{
    return malloc(sizeof(struct alloc));
}

bool alloc_init(alloc* a, size_t size, mark_func mark)
{
    a->ptr = calloc(1, size);
    if (!a->ptr)
    {
        return false;
    }
    a->current_mark = 0;
    a->mark = mark;

    return true;
}

void alloc_mark(alloc* a, int new_mark)
{
    a->current_mark = new_mark;
    a->mark(a->ptr, new_mark);
}

void alloc_destroy(alloc* a)
{
    free(a->ptr);
}

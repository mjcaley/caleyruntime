#include "alloc.h"
#include "type_tag.h"


alloc* alloc_new()
{
    return malloc(sizeof(struct alloc));
}

bool alloc_init(alloc* a, size_t size, TypeTag type)
{
    a->ptr = calloc(1, size);
    if (!a->ptr)
    {
        return false;
    }
    a->current_mark = 0;
    a->type = type;

    return true;
}

// void alloc_mark(alloc* a, int new_mark)
// {
//     a->current_mark = new_mark;
//     a->mark(a->ptr, new_mark);
// }

void alloc_destroy(alloc* a)
{
    free(a->ptr);
}

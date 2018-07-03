#include <stdarg.h>

#include "array.h"


void array_init(Array* self, ...)
{
    va_list valist;

    va_start(valist, self->num);
    for (int i = 0; i < self->size; ++i)
    {

    }

    va_end(valist);
}


void* array_get_element(Array* self, size_t index, bool* error)
{
    if (index >= self->size)
    {
        *error = true;
        return NULL;
    }
    else
    {
        return self->data + (index * self->type->size);
    }
}
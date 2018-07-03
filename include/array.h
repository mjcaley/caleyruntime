#include <stdbool.h>
#include <stddef.h>

#include "gc2.h"


typedef struct Array
{
    size_t size;
    Type2* type;
    void* data;
} Array;

const Type2 Array_TypeInfo =
{
    .size=sizeof(Array),
    .name="Array",
    .offset_len=1,
    .offsets={ offsetof(Array, data) }
}


void array_init(Array* self, ...);
void* array_get_element(Array* self, size_t index, bool* error);
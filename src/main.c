#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc.h"


void traverse_int(void* ptr, void(*f)(void*))
{
    f(ptr);
}

const Type types[] = {
    [0] = { traverse_int, sizeof(int), "int" }
};


int main()
{
    printf(u8"Hello world!\n");

    int* i = gc_malloc(types);
    *i = 42;
    printf("Number: %i\n", *i);

    printf("Mark: %i\n", gc_get_mark(i));
    gc_mark++;
    traverse(i, gc_mark_ptr);
    printf("Mark: %i\n", gc_get_mark(i));

    gc_free(i);

    return 0;
}

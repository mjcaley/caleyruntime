#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "gc_list.h"


void traverse_int(void* ptr, void(*f)(void*))
{
    f(ptr);
}

const Type types[] = {
    [0] = { traverse_int, sizeof(int), "int" }
};

GCList list;


int main()
{
    printf(u8"Hello world!\n");

    gc_list_init(&list);

    int* i = gc_malloc(types);
    *i = 1;
    gc_list_add(&list, i);

    int* i2 = gc_malloc(types);
    *i2 = 2;
    gc_list_add(&list, i2);

    int* i3 = gc_malloc(types);
    *i3 = 3;
    gc_list_add(&list, i3);

    printf("Number: %i\n", *i);

    printf("Mark: %i\n", gc_get_mark(i));
    mark++;
    traverse(i, gc_mark_ptr);
    printf("Mark: %i\n", gc_get_mark(i));

    mark++;
    gc_list_remove(&list, gc_is_not_marked);

    return 0;
}

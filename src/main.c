#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "gc_list.h"

#include "gc2.h"


void traverse_int(void* ptr, void(*f)(void*))
{
    f(ptr);
}

const Type types[] = {
    [0] = { traverse_int, sizeof(int), "int" }
};

GCList list;


void gc1()
{
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
    // gc_list_remove(&list, gc_is_not_marked);
    gc_list_destroy(&list);
}


typedef int32_t i32;
const Type2 TypeInfo_i32 =
{
    .size=sizeof(int32_t),
    .name="int",
    .offset_len=0,
    .offsets={}
};

typedef struct A
{
    int num;
} A;
const Type2 TypeInfo_A =
{
    .size=sizeof(A),
    .name="struct A",
    .offset_len=0,
    .offsets={}
};

typedef struct B
{
    int num;
    A* a;
} B;
const Type2 TypeInfo_B =
{
    .size=sizeof(B),
    .name="struct B",
    .offset_len=1,
    .offsets={offsetof(B, a)}
};

void gc2()
{
    i32* i = gc_malloc2(&TypeInfo_i32);
    *i = 42;
    gc_free2(i);

    A* a = gc_malloc2(&TypeInfo_A);
    a->num = 42;

        B* b = gc_malloc2(&TypeInfo_B);
        b->num = 24;
        b->a = a;

        ++mark;
        // pretend we're looping through roots
        gc_mark_ptr2(b);
        gc_mark_ptr2(a);

        gc_free2(b);

    gc_free2(a);
}


int main()
{
    printf(u8"Hello world!\n");

    gc2();

    return 0;
}

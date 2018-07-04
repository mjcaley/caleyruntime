#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "gc_list.h"


// Allocate on stack example from Cello
// #define alloc_stack(T) header_init( \
//   (char[sizeof(struct Header) + sizeof(struct T)]){0}, T)
//
// var header_init(var head, var type) {
//   struct Header* self = head;
//   self->type = type;
//   return ((char*)self) + sizeof(struct Header);
// }


GCList list;


typedef int32_t i32;
const TypeInfo TypeInfo_i32 =
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
const TypeInfo TypeInfo_A =
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
const TypeInfo TypeInfo_B =
{
    .size=sizeof(B),
    .name="struct B",
    .offset_len=1,
    .offsets={offsetof(B, a)}
};

void gc2()
{
    gc_list_init(&list);

    i32* i = gc_malloc(&TypeInfo_i32);
    gc_list_add(&list, i);
    *i = 42;

    A* a = gc_malloc(&TypeInfo_A);
    gc_list_add(&list, a);
    a->num = 42;

        B* b = gc_malloc(&TypeInfo_B);
        gc_list_add(&list, b);
        b->num = 24;
        b->a = a;
        const Header* const  b_header = gc_get_header(b);
        printf("Header values for A instance:\n\ttype name: %s\n\tsize: %i\n\tlength: %i\n\tmark: %i\n",
               b_header->type->name, b_header->type->size, b_header->length, b_header->mark);

        ++mark;
        // pretend we're looping through roots
        gc_mark_ptr(b);
        gc_mark_ptr(a);

    gc_list_destroy(&list);
}


int main()
{
    printf(u8"Hello world!\n");

    gc2();

    return 0;
}

#include <stdint.h>

// #include "gc2.h"
#include "typeinfo.h"

const TypeInfo i32_def = {
    .size=sizeof(int32_t),
    .name="i32",
    .offset_len=0,
    .offsets={}
};

typedef struct {
    TypeInfo const *const type_tag;
    struct
    {
        int a;
        int b;
    } value;
} Custom;

typedef struct {
    TypeInfo const *const type_tag;
    int32_t value;
} i32;


int main()
{
    // int* integer = alloc_heap(&i32_def);
    // *integer = 42;
    // print_gcheader(integer);
    // alloc_free(integer);

    i32 integer_stack = { .type_tag=&i32_def };
    i32* integer_heap = malloc(sizeof(i32));
    *(i32*)&integer_heap->type_tag = &i32_def; // can't assign to const


    return 0;
}

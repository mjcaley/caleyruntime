#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// #include "gc2.h"
#include "typeinfo.h"

const TypeInfo i32_def = {
    .size=sizeof(int32_t),
    .name="i32",
    .offset_len=0,
    .offsets={}
};

typedef struct {
    TypeInfo* type_tag;
    struct
    {
        int a;
        int b;
    } data;
} Example;

typedef struct {
    TypeInfo const* type_tag;
    int32_t data;
} i32;

typedef struct {
    TypeInfo const* type_tag;
    float data;
} f32;


int main()
{
    // int* integer = alloc_heap(&i32_def);
    // *integer = 42;
    // print_gcheader(integer);
    // alloc_free(integer);

    i32 integer_stack = { .type_tag=&i32_def };

    i32* integer_heap = calloc(1, sizeof(i32));
    integer_heap->type_tag = &i32_def;



    return 0;
}

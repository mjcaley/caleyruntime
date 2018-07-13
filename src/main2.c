#include <stdint.h>

#include "gc2.h"

const TypeInfo i32_def = {
    .size=sizeof(int32_t),
    .name="i32",
    .offset_len=0,
    .offsets={}
};


int main()
{
    int* integer = alloc_heap(&i32_def);
    *integer = 42;
    print_gcheader(integer);
    alloc_free(integer);

    int* integer2 = alloc_stack(&i32_def);
    

    return 0;
}

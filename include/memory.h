#pragma once

#include <stdbool.h>

#include "alloc.h"
#include "alloc_list.h"


typedef struct memory
{
    alloc_list allocated;
    // shadow_stack shadow_stack;
} memory;

alloc* allocate(memory* memory, alloc allocation)
{
    alloc_list_add(&(memory->allocated), allocation);
    return &(memory->allocated->head.allocation);
}

int shadow_stack_push(alloc* allocation)
{
    
}

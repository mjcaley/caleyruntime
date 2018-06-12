#pragma once

#include <stdbool.h>

#include "alloc.h"
#include "alloc_list.h"


typedef struct memory
{
    alloc_list allocated;
    size_t stack_pos;
    size_t stack_size;
    alloc* stack[];
} memory;


bool shadow_stack_new(alloc* stack[], size_t stack_size)
{
    printf("shadow_stack_new stack addr: %p\n", stack);
    alloc* s = calloc(1, sizeof(*stack) + sizeof(alloc*) * stack_size);
    if (s)
    {
        stack = s;
        return true;
    }
    else
    {
        return false;
    }
}


bool memory_init(memory* mem, size_t stack_size)
{
    mem->stack_pos = 0;
    alloc_list_init(&(mem->allocated));
    bool success = shadow_stack_new(mem->stack, stack_size);
    if (success)
    {
        mem->stack_size = stack_size;
    }
    else
    {
        mem->stack_size = 0;
    }

    return success;
}


alloc* shadow_stack_top(memory* mem)
{
    if (mem->stack_pos == 0)
    {
        return NULL;
    }
    else
    {
        return mem->stack[mem->stack_pos];
    }
}



bool shadow_stack_push(memory* mem, alloc* allocation)
{
    if (mem->stack_pos == mem->stack_size)
    {
        return false;
    }

    mem->stack_pos += 1;
    mem->stack[mem->stack_pos] = allocation;

    return true;
}


bool shadow_stack_pop(memory* mem)
{
    if (mem->stack_pos == 0)
    {
        return false;
    }

    mem->stack[mem->stack_pos] = NULL;
    mem->stack_pos -= 1;

    return true;
}
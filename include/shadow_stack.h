#pragma once

struct alloc;


typedef struct shadow_stack
{
    alloc* stack[];
    size_t pos;
} shadow_stack;

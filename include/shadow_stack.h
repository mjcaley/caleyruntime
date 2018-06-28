#pragma once

#include <stddef.h>

#include "gc.h"


typedef struct Locals
{
    GCAlloc* begin;
    GCAlloc* end;
} Locals;

typedef struct ShadowStack
{
    size_t size;
    size_t capacity;
    Locals* locals;
} ShadowStack;




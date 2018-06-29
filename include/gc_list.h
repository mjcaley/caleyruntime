#pragma once

#include <stdbool.h>

#include "gc.h"


typedef struct GCListNode GCListNode;
struct GCListNode
{
    void* data;
    GCListNode* next;
};

typedef struct GCList
{
    GCListNode* head;
} GCList;

void gc_list_init(GCList* list);
void gc_list_add(GCList* list, void* ptr);
void gc_list_remove(GCList* list, bool (*predicate)(void*));

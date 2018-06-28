#pragma once

#include <stddef.h>
#include <stdlib.h>

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

void gc_list_init(GCList* list)
{
    list->head = NULL;
}

void gc_list_add(GCList* list, void* ptr)
{
    GCListNode* new_node = calloc(1, sizeof(GCListNode));
    new_node->data = ptr;
    new_node->next = list->head;
    list->head = new_node;
}

void gc_list_remove(GCList* list, bool (*predicate)(void*))
{
    GCListNode* node = list->head;

    if (!node) { return; }

    GCListNode* prev = NULL;

    while (node)
    {
        prev = node;
        node = prev->next;

        if (predicate(node))
        {
            prev->next = node->next;
        }
    }
}

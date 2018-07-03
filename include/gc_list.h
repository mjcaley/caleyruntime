#pragma once

#include <stdbool.h>


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
void gc_list_remove2(GCList* list, bool (*predicate)(void*));
void gc_list_destroy(GCList* list);
void gc_list_destroy2(GCList* list);

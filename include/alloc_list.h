#pragma once

#include <stdbool.h>

#include "alloc.h"


typedef struct alloc_node
{
    struct alloc allocation;
    struct alloc_node* next;
} alloc_node;

typedef struct alloc_list
{
    alloc_node* head;
} alloc_list;

alloc_node* alloc_node_new();
void alloc_list_init(alloc_list* list);
bool alloc_list_add(alloc_list* list, alloc allocation);
void alloc_list_destroy(alloc_list* list);

#include "alloc_list.h"


alloc_node* alloc_node_new()
{
    return malloc(sizeof(alloc_node));
}

void alloc_node_init(alloc_node* node, alloc allocation)
{
    node->next = NULL;
    node->allocation = allocation;
}

void alloc_list_init(alloc_list* list)
{
    list->head = NULL;
}

bool alloc_list_add(alloc_list* list, alloc allocation)
{
    if (!list) { return false; }
    alloc_node* prev_head = list->head;

    list->head = alloc_node_new();
    if (!list->head) { return false; }
    alloc_node_init(list->head, allocation);

    list->head->next = prev_head;

    return true;
}

void alloc_list_destroy(alloc_list* list)
{
    alloc_node* node = list->head;
    while (node)
    {
        alloc_node* next = node->next;
        alloc_destroy(&(node->allocation));
        free(node);
        node = next;
    }
}

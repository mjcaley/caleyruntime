#include <stdbool.h>
#include <stdlib.h>

#include "gc_list.h"


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
    if (!list->head) { return; }

    GCListNode* head = NULL;
    GCListNode* next = list->head;
    while(next)
    {
        if (predicate(next))
        {
            GCListNode* temp = next->next;
            gc_free(next->data);
            free(next);
            next = temp;
        }
        else
        {
            GCListNode* temp = next->next;
            next->next = head;
            head = next;
            next = temp;
        }
    }

    list->head = head;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// #include "memory.h"
#include "alloc.h"
#include "alloc_list.h"


// Debug stuff
void print_alloc_list(alloc_list* list)
{
    if (!list) { return; }
    alloc_node* node = list->head;
    while (node)
    {
        printf("alloc_node { %p }\n", node->allocation.ptr);
        node = node->next;
    }
}


// Objects and mark functions
struct example;

void mark_int(void* obj, int new_mark) {}

struct A
{
    int number;
};

void mark_a(void* obj, int new_mark) {}

// struct B {
//     A* 
// };

int main()
{
    printf(u8"Hello world!\n");

    alloc a;
    alloc_init(&a, sizeof(int), &mark_int);
    printf("A allocated\n");

    alloc_list list;
    alloc_list_init(&list);
    alloc_list_add(&list, a);
    print_alloc_list(&list);
    alloc_list_destroy(&list);
    // struct alloc_node* list = alloc_node_new();
    // alloc_list_init(list, a);
    // printf("List allocated\n");
    // alloc_list_destroy(list);
    // printf("List destroyed\n");
    // printf("List deallocated\n");

    // printf("Alloc mark: %i\n", a.current_mark);
    // alloc_mark(&a, 1);
    // printf("Alloc mark: %i\n", a.current_mark);
    // alloc_destroy(&a);

    return 0;
}

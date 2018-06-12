#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"
#include "alloc_list.h"
#include "memory.h"


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
    *(int*)(a.ptr) = 42;
    printf("A value: %i\n", *(int*)(a.ptr));
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

    bool ss_success = false;
    // bool a_success = false;
    memory mem;
    memory_init(&mem, 1000);
    printf("mem shadow stack size %i\n", mem.stack_size);
    printf("first: %p, last: %p\n", mem.stack[0], shadow_stack_top(&mem));
    printf("top addr: %p, value: %i\n",
        shadow_stack_top(&mem),
        // *(int*)( (shadow_stack_top(&mem))->ptr )
        *((int*) ( shadow_stack_top(&mem)->ptr ))
    );

    return 0;
}

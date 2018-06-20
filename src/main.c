#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"
#include "alloc_list.h"
#include "memory.h"
#include "gc.h"
#include "type_tag.h"


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

void mark_int(GCAlloc* obj, int new_mark)
{
    if (obj->gc_mark != new_mark)
    {
        obj->gc_mark = new_mark;
    }
}

GCAlloc* int_alloc(GCAllocList* list)
{
    int* ptr = malloc(sizeof(int));
    GCAlloc alloc = { .ptr=ptr, .mark=mark_int, .gc_mark=0 };
    gcalloclist_push(list, alloc);

    return &list->head->node;
}

void int_construct(GCAlloc* alloc, int value)
{
    *(int*)alloc->ptr = value;
}


typedef struct A A;
typedef struct B B;

struct A
{
    GCAlloc* b;
};

struct B
{
    GCAlloc* a;
};


void mark_a(GCAlloc* obj, int new_mark)
{
    if (obj->gc_mark != new_mark)
    {
        obj->gc_mark = new_mark;
        GCAlloc* b = (GCAlloc*)obj->ptr;
        b->mark(b, new_mark);
    }
}

GCAlloc* struct_A_alloc(GCAllocList* list)
{
    GCAlloc alloc = { .ptr=malloc(sizeof(A)), .mark=mark_a, .gc_mark=0 };
    gcalloclist_push(list, alloc);

    return &list->head->node;
}

void struct_A_init(GCAlloc* obj, GCAlloc* b)
{
    obj->ptr = b;
}

void mark_b(GCAlloc* obj, int new_mark)
{
    if (obj->gc_mark != new_mark)
    {
        obj->gc_mark = new_mark;
        GCAlloc* a = (GCAlloc*)obj->ptr;
        a->mark(a, new_mark);
    }
}

GCAlloc* struct_B_alloc(GCAllocList* list)
{
    GCAlloc alloc = { .ptr=malloc(sizeof(B)), .mark=mark_b, .gc_mark=0 };
    gcalloclist_push(list, alloc);

    return &list->head->node;
}

void struct_B_init(GCAlloc* obj, GCAlloc* a)
{
    obj->ptr = a;
}


// struct B {
//     A* 
// };

void print_gc_mark_func_array(GCMarkFuncArray* array)
{
    printf("size: %i, capacity: %i\n", array->size, array->capacity);
}

void print_gc_mark_table(GCMarkTable* table)
{
    for(size_t bucket = 0; bucket < table->buckets; ++bucket)
    {
        print_gc_mark_func_array(&(table->data[bucket]));
    }
}

int main()
{
    printf(u8"Hello world!\n");

    GCAllocList allocation_list = gcalloclist_new();

    GCAlloc* integer1 = int_alloc(&allocation_list);
    int_construct(integer1, 42);
    integer1->mark(integer1, 1);

    printf("Value: %i\n", *(int*)integer1->ptr);
    printf("GC mark: %i\n", integer1->gc_mark);


    GCAlloc* a_inst1 = struct_A_alloc(&allocation_list);
    GCAlloc* b_inst1 = struct_B_alloc(&allocation_list);

    struct_A_init(a_inst1, b_inst1);
    struct_B_init(b_inst1, a_inst1);

    gcalloclist_destroy(&allocation_list);

    // GCMarkTable* mark_funcs = gc_mark_table_new(13);

    // {
    //     GCMarkFunc temporary = { .type=INTEGER, .mark=mark_int };
    //     gc_mark_table_insert(mark_funcs, temporary);
    // }
    // {
    //     GCMarkFunc temporary = { .type=INTEGER, .mark=mark_int };
    //     gc_mark_table_insert(mark_funcs, temporary);
    // }
    // {
    //     GCMarkFunc temporary = { .type=INTEGER, .mark=mark_int };
    //     gc_mark_table_insert(mark_funcs, temporary);
    // }
    // {
    //     GCMarkFunc temporary = { .type=INTEGER, .mark=mark_int };
    //     gc_mark_table_insert(mark_funcs, temporary);
    // }

    // print_gc_mark_table(mark_funcs);

    // gc_mark_table_destroy(mark_funcs);
    // free(mark_funcs);

    return 0;
}

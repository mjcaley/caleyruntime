#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "type_tag.h"


typedef struct GCAlloc
{
    void* ptr;
    void (*mark)(void*, int);
    int gc_mark;
} GCAlloc;

typedef struct GCAllocNode GCAllocNode;
struct GCAllocNode
{
    GCAlloc node;
    GCAllocNode* next;
};

typedef struct GCAllocList
{
    GCAllocNode* head;
} GCAllocList;


void gcalloc_destroy(GCAlloc* alloc)
{
    free(alloc->ptr);
}

// void gcallocnode_destroy(GCAllocNode* node)
// {
//     gcalloc_destroy(node->node);
//     free(node);
// }


GCAllocList gcalloclist_new()
{
    GCAllocList list = { .head=NULL };
    return list;
}

void gcalloclist_push(GCAllocList* list, GCAllocNode* node)
{
    node->next = list->head;
    list->head = node;
}

void gcalloclist_foreach(GCAllocList* list, void (*func)(GCAllocNode*) )
{
    GCAllocNode* node = list->head;
    while(node)
    {
        func(node);
        node = node->next;
    }
}

void gcalloclist_remove(GCAllocList* list, bool (*predicate)(GCAllocNode*) )
{
    GCAllocNode* node = list->head;
    while(node)
    {
        if (predicate(node))
        {
            free(node->node.ptr);
            free(node);
        }
    }
}

void gcalloclist_destroy(GCAllocList* list)
{

}




typedef struct GCMarkFunc
{
    TypeTag type;
    void (*mark)(void*, int);
} GCMarkFunc;

typedef struct GCMarkFuncArray
{
    size_t size;
    size_t capacity;
    GCMarkFunc* functions;
} GCMarkFuncArray;

typedef struct GCMarkTable
{
    size_t size;
    size_t buckets;
    GCMarkFuncArray* data;
} GCMarkTable;


// GCMarkFuncArray functions

void gc_mark_func_array_init(GCMarkFuncArray* array)
{
    if (array)
    {
        array->size = 0;
        array->capacity = 0;
        array->functions = NULL;
    }
}

GCMarkFuncArray* gc_mark_func_array_new()
{
    GCMarkFuncArray* array = malloc(sizeof(*array));
    gc_mark_func_array_init(array);

    return array;
}

void gc_mark_func_array_resize(GCMarkFuncArray* array, size_t size)
{
    GCMarkFunc* old = array->functions;
    GCMarkFunc* new = realloc(old, sizeof(GCMarkFunc) * size);
    if (new)
    {
        array->functions = new;
        array->capacity = size;
    }
}

void gc_mark_func_array_insert(GCMarkFuncArray* array, GCMarkFunc func)
{
    if (array->size == array->capacity)
    {
        gc_mark_func_array_resize(array, array->size * 2 + 1);
    }

    array->functions[array->size] = func;
    ++array->size;
}

void gc_mark_func_array_remove(GCMarkFuncArray* array, size_t position)
{
    for (; position < array->size; ++position)
    {
        array->functions[position] = array->functions[position + 1];
    }
    --array->size;
}

void gc_mark_func_array_shrink(GCMarkFuncArray* array)
{
    gc_mark_func_array_resize(array, array->size);
}

void gc_mark_func_array_destroy(GCMarkFuncArray* array)
{
    free(array->functions);
}


// GCMarkTable functions

GCMarkTable* gc_mark_table_new(size_t num_buckets)
{
    GCMarkTable* table = malloc(sizeof(*table));
    if (table)
    {
        table->size = 0;
        table->buckets = num_buckets;
        table->data = calloc(table->buckets, sizeof(GCMarkFuncArray));
        for (size_t i = 0; i < table->buckets; ++i)
        {
            gc_mark_func_array_init(&(table->data[i]));
            // table->data[i] = gc_mark_func_array_new();
        }
    }

    return table;
}

void gc_mark_table_insert(GCMarkTable* table, GCMarkFunc func)
{
    size_t bucket = func.type % table->buckets;
    for (size_t index = 0; index < table->data[bucket].size; ++index)
    {
        if (table->data[bucket].functions[index].type == func.type)
        {
            table->data[bucket].functions[index].mark = func.mark;
            return;
        }
    }

    gc_mark_func_array_insert(&(table->data[bucket]), func);
}

void gc_mark_table_destroy(GCMarkTable* table)
{
    for (size_t bucket = 0; bucket < table->buckets; ++bucket)
    {
        gc_mark_func_array_destroy(&(table->data[bucket]));
    }
    free(table->data);
}

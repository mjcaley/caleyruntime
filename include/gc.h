#pragma once

#include <stddef.h>
#include <stdlib.h>
#include "tags.h"


typedef struct AllocationNode AllocationNode;
struct AllocationNode {
	AllocationNode* next;
	TypeTag allocation;
};

typedef struct AllocationList {
	AllocationNode* head;
} AllocationList;

void init_allocation_list(AllocationList* a);
AllocationNode* create_allocation(size_t size);
void add_allocation(AllocationList* list, AllocationNode* node);
void* get_object_pointer(AllocationNode* node);

void gc_mark(AllocationList* list, int mark);

void mark_list_add(TypeTag* mark_list[], size_t* mark_list_len, TypeTag* ptr);
void mark_value_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ValueTag* v);
void mark_array_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ArrayTag* a);
void mark_ref_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ReferenceTag* r);
void mark(TypeTag* mark_list[], size_t* mark_list_len, int new_mark);

void init_gc(TypeTag* t);

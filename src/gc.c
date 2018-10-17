#include <stdlib.h>
#include "gc.h"
#include "tags.h"
#include "type_definition.h"
#include "pointer_queue.h"


void init_allocation_list(AllocationList* list) {
	list->head = NULL;
}

AllocationNode* create_allocation(size_t size) {
	return calloc(1, sizeof(AllocationNode*) + size);
}

void* get_object_pointer(AllocationNode* node) {
	return &(node->allocation);
}

void add_allocation(AllocationList* list, AllocationNode* node) {
	node->next = list->head;
	list->head = node;
}

static void gc_mark_queue_references(PointerQueue* queue, void* object, TypeDefinition* type_def) {
	for (size_t i = 0; i < type_def->num_offsets; ++i) {
		void* next_reference = (char*)object + type_def->offsets[i];
		push_pointer_queue(queue, next_reference);
	}
}

static void gc_mark_value(ValueTag* allocation, PointerQueue* queue, const int mark) {
	if (allocation->gc.mark == mark) {
		return;
	}

	allocation->gc.mark = mark;

	void* object = (char*)allocation + sizeof(ValueTag);
	gc_mark_queue_references(queue, object, allocation->type_def);
}

static void gc_mark_array(ArrayTag* allocation, PointerQueue* queue, const int mark) {
	if (allocation->gc.mark == mark) {
		return;
	}

	allocation->gc.mark = mark;

	for (size_t i = 0;
		i < allocation->length;
		++i) {
		void* object = (char*)allocation + sizeof(ArrayTag);
		void* element = (char*)object + allocation->type_def->size * i;
		gc_mark_queue_references(queue, element, allocation->type_def);
	}
}

static void gc_mark_reference(ReferenceTag* allocation, PointerQueue* queue, const int mark) {
	void* object = (char*)allocation + sizeof(ReferenceTag);
	push_pointer_queue(queue, object);
}

void gc_mark(PointerQueue* queue, const int mark) {
	void* value;
	while (value = pop_pointer_queue(&queue)) {
		AllocationNode* alloc = (AllocationNode*)value;
		switch (alloc->allocation.tag) {
		case ValueType:
			gc_mark_value((ValueTag*)alloc, &queue, mark);
		case ArrayType:
			gc_mark_array((ArrayTag*)alloc, &queue, mark);
		case ReferenceType:
			gc_mark_reference((ReferenceTag*)alloc, &queue, mark);
		default:
			break;
		}
	}
}

void gc_sweep(AllocationList* list, int mark) {
	AllocationList new_list;
	init_allocation_list(&new_list);

	AllocationNode* node = list->head;
	while (node) {
		TypeTag* tag = &node->allocation;
		switch (node->allocation.tag) {
		case ValueType:
			if ( ((ValueTag*)tag)->gc.mark == mark) {
				add_allocation(&new_list, node);
				node = node->next;
			}
			else {
				AllocationNode* orig = node;
				node = orig->next;
				free(orig);
			}
			break;
		case ArrayType:
			if (((ArrayTag*)tag)->gc.mark == mark) {
				add_allocation(&new_list, node);
				node = node->next;
			}
			else {
				AllocationNode* orig = node;
				node = orig->next;
				free(orig);
			}
			break;
		}
	}

	list->head = new_list.head;
}

void gc_collect(AllocationList* allocations, const int mark) {
	// gets stack frames
	// collects roots into PointerQueue
	// calls gc_mark
	// calls gc_sweep

	PointerQueue queue;
	init_pointer_queue(&queue);
	gc_mark(&queue, mark);
	destroy_pointer_queue(&queue);

	gc_sweep(allocations, mark);
}

void mark_list_add(TypeTag* mark_list[], size_t* mark_list_len, TypeTag* ptr) {
	mark_list[*mark_list_len] = ptr;
	(*mark_list_len)++;
}

void mark_value_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ValueTag* v) {
	if (v->gc.mark != new_mark) {
		v->gc.mark = new_mark;
		for (int offset_i = 0; offset_i < v->type_def->num_offsets; ++offset_i) {
			void* offset_ptr = (char*)v + v->type_def->offsets[offset_i];
			mark_list_add(mark_list, mark_list_len, offset_ptr);
		}
	}
}

void mark_array_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ArrayTag* a) {
	if (a->gc.mark != new_mark) {
		a->gc.mark = new_mark;
		for (int element_index = 0; element_index < a->length; ++element_index) {
			for (int offset_i = 0; offset_i < a->type_def->num_offsets; ++offset_i) {
				void* offset_ptr = (char*)a + a->type_def->offsets[offset_i];
				mark_list_add(mark_list, mark_list_len, offset_ptr);
			}
		}
	}
}

void mark_ref_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ReferenceTag* r) {
	mark_list_add(mark_list, mark_list_len, (TypeTag*)(r + 1));
}

void mark(TypeTag* mark_list[], size_t* mark_list_len, int new_mark) {
	for (size_t i = 0; i < *mark_list_len; ++i) {
		if (!mark_list[i]) { continue; }

		if (mark_list[i]->tag == ValueType) {
			mark_value_type(mark_list, mark_list_len, new_mark, (ValueTag*)mark_list[i]);
		}

		else if (mark_list[i]->tag == ArrayType) {
			mark_array_type(mark_list, mark_list_len, new_mark, (ArrayTag*)mark_list[i]);
		}

		else if (mark_list[i]->tag == ReferenceType) {
			mark_ref_type(mark_list, mark_list_len, new_mark, (ReferenceTag*)mark_list[i]);
		}
	}
}

void init_gc(TypeTag* t) {
	switch (t->tag) {
	case ValueType:
		((ValueTag*)t)->gc.mark = 0;
		break;
	case ArrayType:
		((ArrayTag*)t)->gc.mark = 0;
		break;
	}
}

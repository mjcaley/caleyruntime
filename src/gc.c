#include "gc.h"
#include "tags.h"
#include "type_definition.h"


void init_allocation_list(AllocationList* list) {
	list->head = NULL;
}

void add_allocation(AllocationList* list, AllocationNode* node) {
	node->next = list->head;
	list->head = node;
}

void gc_mark(AllocationList* list, int mark) {

}

void gc_sweep(AllocationList* list, int mark) {
	AllocationList new_list = { .head = NULL };

	AllocationNode* node = list->head;
	while (node) {
		switch (node->allocation.tag) {
		case ValueType:
			if (((ValueTag*)node->allocation)->gc.mark == mark) {
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
			if (((ArrayTag*)node->allocation)->gc.mark == mark) {
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

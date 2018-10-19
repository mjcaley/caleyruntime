#include <stdlib.h>

#include "greatest.h"

#include "gc.h"
#include "type_definition.h"
#include "pointer_queue.h"


TEST allocation_list_head_null(AllocationList* list) {
	init_allocation_list(list);
	ASSERT(NULL == list->head);
	PASS();
}

SUITE(allocation_list) {
	AllocationList list;

	RUN_TESTp(allocation_list_head_null, &list);
}

void setup_new_allocation_list(void* data) {
	AllocationList* list = (AllocationList*)data;
	list->head = NULL;
}

void teardown_new_allocation_list(void* data) {
	AllocationList* list = (AllocationList*)data;
	list->head = NULL;
}

TEST add_allocation_to_list(AllocationList* list) {
	AllocationNode node = { .next = NULL,.allocation = ReferenceType };
	add_allocation(list, &node);

	if (!list->head) { FAIL(); }
	ASSERT(list->head);
	ASSERT_EQ(&node, list->head);
	PASS();
}

TEST create_an_allocation() {
	AllocationNode* node = create_allocation(sizeof(int));
	ASSERT(node);
	free(node);
	PASS();
}

SUITE(empty_allocation_list) {
	AllocationList list;
	SET_SETUP(setup_new_allocation_list, &list);
	SET_TEARDOWN(teardown_new_allocation_list, &list);

	RUN_TESTp(add_allocation_to_list, &list);

	SET_SETUP(NULL, NULL);
	SET_TEARDOWN(NULL, NULL);
}

TEST return_object_from_allocation() {
	AllocationNode a = { .next=NULL, .allocation=ArrayType };
	void* object = get_object_pointer(&a);

	ASSERT_EQ(&a.allocation, object);
	PASS();
}


TEST empty_queue_not_marked() {
	PointerQueue queue;
	init_pointer_queue(&queue);
	gc_mark(&queue, 42);
	destroy_pointer_queue(&queue);

	PASS();
}


typedef struct MockType {
	int value;
} MockType;

typedef struct MockValue {
	ValueTag header;
	MockType mock_type;
} MockValue;

TypeDefinition mock_value_def = {
	.name="MockValue",
	.size=sizeof(MockType),
	.num_offsets=0,
	.offsets=NULL
};

TEST value_type_marked() {
	PointerQueue queue;
	init_pointer_queue(&queue);

	MockValue v = { .mock_type.value = 1 };
	init_value_tag(&v, &mock_value_def);
	push_pointer_queue(queue, &v);

	gc_mark(queue, 42);

	ASSERT_EQ(42, v.header.gc.mark);
	PASS();
}


typedef struct MockArray {
	ValueTag header;
	MockType mock_type[];
} MockArray;

TEST array_type_marked(PointerQueue* queue) {
	MockArray* a = malloc(sizeof(MockArray) + sizeof(MockType) * 3);
	init_value_tag(a, &mock_value_def);
	push_pointer_queue(queue, a);

	gc_mark(queue, 42);

	if (!setjmp(test_passed)) {
		ASSERT(24 == a->header.gc.mark);
	}

	free(a);
	PASS();
}

SUITE(mark_functions) {
	PointerQueue queue;
	SET_SETUP(setup_pointer_queue, &queue);
	SET_TEARDOWN(teardown_pointer_queue, &queue);

	RUN_TESTp(empty_queue_not_marked, &queue);
	RUN_TESTp(value_type_marked, &queue);
	RUN_TESTp(array_type_marked, &queue);

	SET_SETUP(NULL, NULL);
	SET_TEARDOWN(NULL, NULL);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(allocation_list);
	RUN_SUITE(empty_allocation_list);
	RUN_TEST(create_an_allocation);
	RUN_TEST(return_object_from_allocation);
	RUN_SUITE(mark_functions);

	GREATEST_MAIN_END();
}

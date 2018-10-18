#include <stdlib.h>

#include "greatest.h"

#include "gc.h"


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

SUITE(mark_functions) {

}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(allocation_list);
	RUN_SUITE(empty_allocation_list);
	RUN_TEST(create_an_allocation);
	RUN_TEST(return_object_from_allocation);

	GREATEST_MAIN_END();
}

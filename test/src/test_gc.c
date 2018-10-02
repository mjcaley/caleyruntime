#include "unity.h"
#include "gc.h"


AllocationList* list;

void setUp() {
	list = malloc(sizeof(AllocationList));
}
void tearDown() {
	free(list);
}

void test_init_allocation_list() {
  init_allocation_list(list);
  TEST_ASSERT_NULL(list->head);
}

void test_add_allocation() {
	AllocationNode node;
	TypeTag tag;
	node.allocation = &tag;
	node.next = NULL;

	add_allocation(list, &node);

	TEST_ASSERT_EQUAL_PTR(&node, list->head);
}

void test_create_allocation() {
	TypeTag tag;
	create_allocation(list, &tag);

	TEST_ASSERT_EQUAL_PTR(&tag, list->head->allocation);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_init_allocation_list);
  RUN_TEST(test_add_allocation);
  RUN_TEST(test_create_allocation);

  return UNITY_END();
}

#include "unity.h"
#include "gc.h"


void setUp() {}
void tearDown() {}

void test_init_allocation_list() {
	AllocationList list;
	init_allocation_list(&list);
	TEST_ASSERT_NULL(list.head);
}

void test_add_allocation() {
	AllocationList list;
	AllocationNode node;
	TypeTag tag;
	node.allocation = &tag;
	node.next = NULL;

	add_allocation(&list, &node);

	TEST_ASSERT_EQUAL_PTR(&node, list.head);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_init_allocation_list);
  RUN_TEST(test_add_allocation);

  return UNITY_END();
}

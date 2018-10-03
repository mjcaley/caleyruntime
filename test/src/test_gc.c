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
	init_allocation_list(&list);
	AllocationNode node = { .next = NULL, .allocation = {.tag = ValueType} };

	add_allocation(&list, &node);

	TEST_ASSERT_EQUAL_PTR(&node, list.head);
}

void test_create_allocation() {
	AllocationNode* node = create_allocation(sizeof(int));

	TEST_ASSERT_NOT_NULL(node);
}

typedef struct Integer {
	ValueTag header;
	int value;
} Integer;

void test_get_object_pointer() {
	AllocationNode* node = create_allocation(sizeof(Integer));
	Integer* value_ptr = get_object_pointer(node);

	TEST_ASSERT_EQUAL_PTR(&(node->allocation), value_ptr);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_init_allocation_list);
  RUN_TEST(test_add_allocation);
  RUN_TEST(test_create_allocation);
  RUN_TEST(test_get_object_pointer);

  return UNITY_END();
}

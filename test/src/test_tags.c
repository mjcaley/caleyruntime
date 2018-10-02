#include "unity.h"
#include "tags.h"

void setUp() {}
void tearDown() {}

void test_init_type_tag_value() {
	TypeTag t;

	init_type_tag(&t, ValueType);
	TEST_ASSERT_EQUAL(ValueType, t.tag);
}

void test_init_type_tag_reference() {
	TypeTag t;

	init_type_tag(&t, ReferenceType);
	TEST_ASSERT_EQUAL(ReferenceType, t.tag);
}

void test_init_type_tag_array() {
	TypeTag t;

	init_type_tag(&t, ArrayType);
	TEST_ASSERT_EQUAL(ArrayType, t.tag);
}

void main() {
	UNITY_BEGIN();

	RUN_TEST(test_init_type_tag_value);
	RUN_TEST(test_init_type_tag_reference);
	RUN_TEST(test_init_type_tag_array);

	return UNITY_END();
}

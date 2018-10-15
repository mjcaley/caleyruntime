#include <stdlib.h>

#include "greatest.h"

#include "tags.h"


void reset_tag_type(void* data) {
	TypeTag* t = (TypeTag*)data;
	t->tag = -1;
}

TEST type_tag_initialized(TypeTag* tag, Type type) {
	init_type_tag(tag, type);

	ASSERT_EQ(type, tag->tag);
	PASS();
}

SUITE(initialize_type_tag) {
	TypeTag tag;

	SET_SETUP(reset_tag_type, &tag);
	SET_TEARDOWN(NULL, NULL);

	RUN_TESTp(type_tag_initialized, &tag, ValueType);
	RUN_TESTp(type_tag_initialized, &tag, ArrayType);
	RUN_TESTp(type_tag_initialized, &tag, ReferenceType);

	SET_SETUP(NULL, NULL);
	SET_TEARDOWN(NULL, NULL);
}


const char* type_string(int t) {
	switch ((Type)t) {
	case ValueType:
		return "ValueType";
		break;
	case ArrayType:
		return "ArrayType";
		break;
	case ReferenceType:
		return "ReferenceType";
		break;
	default:
		return "Invalid type value";
		break;
	}
}

TEST initialize_value_tag(ValueTag* t) {
	init_value_tag(t, NULL);

	ASSERT_ENUM_EQ(ValueType, t->type.tag, type_string);
	ASSERT_EQ(NULL, t->type_def);
	
	PASS();
}

TEST initialize_array_tag(ArrayTag* t) {
	init_array_tag(t, NULL, 42);

	ASSERT_ENUM_EQ(ArrayType, t->type.tag, type_string);
	ASSERT_EQ(NULL, t->type_def);
	ASSERT_EQ(42, t->length);

	PASS();
}

TEST initialize_reference_tag(ReferenceTag* t) {
	init_reference_tag(t);

	ASSERT_ENUM_EQ(ReferenceType, t->type.tag, type_string);

	PASS();
}

SUITE(initialize_tags_specialized) {
	ValueTag v;
	v.type.tag = -1;
	RUN_TESTp(initialize_value_tag, &v);

	ArrayTag a;
	a.type.tag = -1;
	RUN_TESTp(initialize_array_tag, &a);

	ReferenceTag r;
	r.type.tag = -1;
	RUN_TESTp(initialize_reference_tag, &r);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(initialize_type_tag);
	RUN_SUITE(initialize_tags_specialized);

	GREATEST_MAIN_END();
}

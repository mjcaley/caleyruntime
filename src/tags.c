#include "tags.h"


void init_type_tag(TypeTag* tag, Type type) {
	tag->tag = type;
}

void init_reference_tag(ReferenceTag* tag) {
	init_type_tag(&tag->type, ReferenceType);
}

void init_value_tag(ValueTag* tag, TypeDefinition* type_def) {
	init_type_tag(&tag->type, ValueType);
	tag->gc.mark = 0;
	tag->type_def = type_def;
}

void init_array_tag(ArrayTag* tag, TypeDefinition* type_def, size_t length) {
	init_type_tag(&tag->type, ArrayType);
	tag->gc.mark = 0;
	tag->type_def = type_def;
	tag->length = length;
}

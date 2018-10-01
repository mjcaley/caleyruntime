#pragma once

#include <stddef.h>


typedef struct TypeDefinition TypeDefinition;

typedef enum Type {
	ValueType,
	ReferenceType,
	ArrayType
} Type;

typedef struct TypeTag {
	Type tag;
} TypeTag;

typedef struct GCHeader {
	int mark;
} GCHeader;


typedef struct ReferenceTag {
	TypeTag type;
	// Pointer to type
} ReferenceTag;

typedef struct ValueTag {
	TypeTag type;
	GCHeader gc;
	TypeDefinition* type_def;
	// Object
} ValueTag;

typedef struct ArrayTag {
	TypeTag type;
	GCHeader gc;
	TypeDefinition* type_def;
	size_t length;
	// Array of objects
} ArrayTag;

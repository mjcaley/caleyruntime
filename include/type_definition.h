#pragma once

#include <stddef.h>


typedef struct TypeDefinition {
	const char* name;
	size_t size;
	size_t num_offsets;
	size_t offsets[];
} TypeDefinition;

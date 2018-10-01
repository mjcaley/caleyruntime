#pragma once

#include <stddef.h>
#include "tags.h"


void mark_list_add(TypeTag* mark_list[], size_t* mark_list_len, TypeTag* ptr);
void mark_value_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ValueTag* v);
void mark_array_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ArrayTag* a);
void mark_ref_type(TypeTag* mark_list[], size_t* mark_list_len, int new_mark, ReferenceTag* r);
void mark(TypeTag* mark_list[], size_t* mark_list_len, int new_mark);

void init_gc(TypeTag* t);

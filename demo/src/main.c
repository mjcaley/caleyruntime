#include <stdio.h>

#include "tags.h"
#include "type_definition.h"
#include "gc.h"




typedef struct A A;
typedef struct B B;

typedef struct A {
	ValueTag header;
	int a;
	int b;
} A;

typedef struct A_Reference {
	ReferenceTag header;
	A* ref;
} A_Reference;

TypeDefinition A_TypeDef = {
	.name = "A",
	.size = sizeof(A),
	.num_offsets = 0
};

typedef struct B {
	ValueTag header;
	A_Reference a;
} B;

typedef struct B_Reference {
	ReferenceTag header;
	B* ref;
} B_Reference;

TypeDefinition B_TypeDef = {
	.name = "B",
	.size = sizeof(B),
	.num_offsets = 1,
	.offsets = {offsetof(B, a)}
};


TypeTag* mark_list[1000] = { 0 };
size_t mark_list_len = 0;
int gc_mark = 0;

int main() {
	A a;
	// init_header_value((Value*)&a, &A_TypeDef);
	a.header.type = Type { ValueType };
	a.header.type_def = &A_TypeDef;
	a.a = 42;
	a.b = 43;

	B b;
	// init_header_value((Value*)&b, &B_TypeDef);
	b.header.type = ValueType;
	b.header.type_def = &B_TYpeDef;
	{
		//Reference r_temp;
		B_Reference r_temp;
		//init_header_reference(&r_temp);
		r_temp.header.type = ReferenceType;
		//r_temp.ref = &a;
		r_temp.header.ref = &a;
		b.a = r_temp;
	}

	// Test cycles, if it goes into an infinite loop then we've got a problem
	B c1, c2;
	//init_header_value((Value*)&c1, &B_TypeDef);
	c1.header.type = ValueType;
	c1.header.type_def = &B_TypeDef;
	//init_header_value((Value*)&c2, &B_TypeDef);
	c2.header.type = ValueType;
	c2.header.type_def = &B_TypeDef;
	c1.a = B_Reference { .tag=ReferenceType, .ref=&c2 };
	//c1.a = make_reference(&c2);
	c2.a = B_Reference{ .tag = ReferenceType,.ref = &c1 };
	// c2.a = make_reference(&c1);
	mark_list_add(mark_list, &mark_list_len, (TypeHeader*)&c1);
	mark_list_add(mark_list, &mark_list_len, (TypeHeader*)&c2);


	// Test marking child objects

	B d1;
	A d2;
	init_header_value((Value*)&d1, &B_TypeDef);
	init_header_value((Value*)&d2, &A_TypeDef);
	d1.a = make_reference(&d2);
	mark_list_add(mark_list, &mark_list_len, (TypeHeader*)&d1); // Only add the first object


	printf("A mark: %i\n", a.header.gc.mark);
	printf("B mark: %i\n", b.header.gc.mark);
	printf("C1 mark: %i\n", c1.header.gc.mark);
	printf("C2 mark: %i\n", c2.header.gc.mark);
	printf("D1 mark: %i\n", d1.header.gc.mark);
	printf("D2 mark: %i\n", d2.header.gc.mark);

	mark_list_add(mark_list, &mark_list_len, (TypeHeader*)&a);
	mark_list_add(mark_list, &mark_list_len, (TypeHeader*)&b);
	gc_mark++;
	mark(mark_list, &mark_list_len, gc_mark);

	printf("A mark: %i\n", a.header.gc.mark);
	printf("B mark: %i\n", b.header.gc.mark);
	printf("C1 mark: %i\n", c1.header.gc.mark);
	printf("C2 mark: %i\n", c2.header.gc.mark);
	printf("D1 mark: %i\n", d1.header.gc.mark);
	printf("D2 mark: %i\n", d2.header.gc.mark);

	printf("A contents: %i, %i, %p\n", a.a, a.b, &a);
	printf("B contents: %p, %p\n", b.a.ref, &b);

	return 0;
}

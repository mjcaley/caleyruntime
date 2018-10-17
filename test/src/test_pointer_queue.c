#include <stdlib.h>

#include "greatest.h"

#include "pointer_queue.h"


void reset_pointer_queue(void* data) {
	PointerQueue* p = (PointerQueue*)data;
	PointerQueueNode* node = p->head;
	while (node) {
		PointerQueueNode* next = node->next;
		free(node);
		node = next;
	}
	p->head = NULL;
	p->tail = NULL;
}

TEST init_pointer_queue_head_and_tail_null(PointerQueue* queue) {
	init_pointer_queue(queue);

	ASSERT_EQ(NULL, queue->head);
	ASSERT_EQ(NULL, queue->tail);
	PASS();
}

TEST push_pointer_queue_has_head_and_tail(PointerQueue* queue) {
	init_pointer_queue(queue);
	int i = 42;
	push_pointer_queue(queue, &i);

	ASSERT_EQ(&i, queue->head->value);
	ASSERT_EQ(&i, queue->tail->value);
	PASS();
}

TEST push_pointer_queue_multiple_nodes(PointerQueue* queue) {
	init_pointer_queue(queue);
	int i1, i2, i3;
	push_pointer_queue(queue, &i1);
	push_pointer_queue(queue, &i2);
	push_pointer_queue(queue, &i3);

	ASSERT_EQ(&i1, queue->head->value);
	ASSERT_EQ(&i2, queue->head->next->value);
	ASSERT_EQ(&i3, queue->head->next->next->value);
	ASSERT_EQ(&i3, queue->tail->value);
	PASS();
}

TEST pop_empty_pointer_queue_is_null(PointerQueue* queue) {
	init_pointer_queue(queue);
	void* popped = pop_pointer_queue(queue);

	ASSERT_EQ(NULL, popped);
	PASS();
}

TEST pop_off_of_head(PointerQueue* queue) {
	init_pointer_queue(queue);
	int i1, i2, i3;
	push_pointer_queue(queue, &i1);
	push_pointer_queue(queue, &i2);
	push_pointer_queue(queue, &i3);

	void* popped = pop_pointer_queue(queue);
	ASSERT_EQ(&i1, popped);
	PASS();
}

TEST pop_until_empty(PointerQueue* queue) {
	init_pointer_queue(queue);
	int i1, i2, i3;
	push_pointer_queue(queue, &i1);
	push_pointer_queue(queue, &i2);
	push_pointer_queue(queue, &i3);

	void* value = NULL;
	value = pop_pointer_queue(queue);
	ASSERT_EQ(&i1, value);
	value = pop_pointer_queue(queue);
	ASSERT_EQ(&i2, value);
	value = pop_pointer_queue(queue);
	ASSERT_EQ(&i3, value);
	value = pop_pointer_queue(queue);
	ASSERT_EQ(NULL, value);
	PASS();
}

TEST destroy_head_and_tail_is_null(PointerQueue* queue) {
	init_pointer_queue(queue);
	int i1, i2, i3;
	push_pointer_queue(queue, &i1);
	push_pointer_queue(queue, &i2);
	push_pointer_queue(queue, &i3);
	destroy_pointer_queue(queue);

	ASSERT_EQ(NULL, queue->head);
	ASSERT_EQ(NULL, queue->tail);
	PASS();
}

SUITE(pointer_queue_tests) {
	PointerQueue queue;
	SET_SETUP(NULL, NULL);
	SET_TEARDOWN(reset_pointer_queue, &queue);

	RUN_TESTp(init_pointer_queue_head_and_tail_null, &queue);
	RUN_TESTp(push_pointer_queue_has_head_and_tail, &queue);
	RUN_TESTp(push_pointer_queue_multiple_nodes, &queue);
	RUN_TESTp(pop_off_of_head, &queue);
	RUN_TESTp(pop_empty_pointer_queue_is_null, &queue);
	RUN_TESTp(destroy_head_and_tail_is_null, &queue);
	RUN_TESTp(pop_until_empty, &queue);

	SET_TEARDOWN(NULL, NULL);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(pointer_queue_tests);

	GREATEST_MAIN_END();
}

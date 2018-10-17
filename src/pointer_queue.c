#include <stdlib.h>

#include "pointer_queue.h"


void init_pointer_queue(PointerQueue* queue) {
	queue->head = NULL;
	queue->tail = NULL;
}

void push_pointer_queue(PointerQueue* queue, void* value) {
	PointerQueueNode* node = calloc(1, sizeof(PointerQueueNode));
	node->value = value;
	
	if (!queue->head || !queue->tail) {
		queue->head = node;
		queue->tail = node;
	}
	else {
		queue->tail->next = node;
		queue->tail = node;
	}
}

void* pop_pointer_queue(PointerQueue* queue) {
	if (!queue->head) {
		return NULL;
	};

	PointerQueueNode* node = queue->head;
	void* node_value = node->value;
	queue->head = queue->head->next;
	free(node);

	return node_value;
}

void destroy_pointer_queue(PointerQueue* queue) {
	PointerQueueNode* node = queue->head;

	while (node) {
		PointerQueueNode* next = node->next;
		free(node);
		node = next;
	}

	queue->head = NULL;
	queue->tail = NULL;
}

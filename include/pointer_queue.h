#pragma once

typedef struct PointerQueueNode PointerQueueNode;
struct PointerQueueNode {
	PointerQueueNode* next;
	void* value;
};

typedef struct PointerQueue {
	PointerQueueNode* head;
	PointerQueueNode* tail;
} PointerQueue;


void init_pointer_queue(PointerQueue* queue);
void push_pointer_queue(PointerQueue* queue, void* value);
void* pop_pointer_queue(PointerQueue* queue);
void destroy_pointer_queue(PointerQueue* queue);

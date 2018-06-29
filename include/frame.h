#pragma once

#include <stddef.h>


typedef struct FrameNode FrameNode;
struct FrameNode
{
    size_t num;
    void* locals[];
    FrameNode* next;
};

typedef struct FrameList
{
    FrameNode* head;
} FrameList;


void frame_push(FrameList* stack, FrameNode* frame)
{
    frame->next = stack->head;
    head = frame;
}


void frame_pop(FrameList* stack)
{
    FrameNode* head = stack->head;
    free(stack->head);
    stack->head = head;
}

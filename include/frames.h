#pragma once

#include <stddef.h>
#include <stdlib.h>


// typedef struct FrameNode FrameNode;
// struct FrameNode
// {
//     FrameNode* next;
//     size_t num;
//     void* locals[];
// };

// typedef struct FrameList
// {
//     FrameNode* head;
// } FrameList;


// void frame_push(FrameList* stack, FrameNode* frame)
// {
//     frame->next = stack->head;
//     stack->head = frame;
// }


// void frame_pop(FrameList* stack)
// {
//     FrameNode* head = stack->head;
//     free(stack->head);
//     stack->head = head;
// }

typedef struct Frame
{
    size_t size;
    void* locals[];
} Frame;


typedef struct Frames
{
    size_t size;
    size_t capacity;

    Frame** frames;
} Frames;


void frames_init(Frames* self)
{
    self->size = 0;
    self->capacity = 0;
    self->frames = (Frame**)malloc(0);
}

void frames_resize(Frames* self, size_t new_size)
{
    self->frames = realloc(self->frames, new_size);
    self->capacity = new_size;
}

Frame* frames_push(Frames* self, Frame* frame)
{
    if (self->capacity == self->size)
    {
        frames_resize(self, self->capacity*2);
    }

    self->frames[self->size+1] = frame;
    self->size++;

    return frame;
}

Frame* frames_pop(Frames* self)
{
    Frame* pop = self->frames[self->size];
    self->size--;
    
    return pop;
}

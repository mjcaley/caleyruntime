#pragma once

#include <stddef.h>


typedef struct Frame
{
    size_t num;
    void* locals[];
} Frame;

typedef struct FrameNode FrameNode;
struct FrameNode
{
    Frame* frame;
    FrameNode* next;
};

typedef struct FrameList
{
    FrameNode* head;
} FrameList;

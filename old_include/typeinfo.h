#pragma once

typedef struct TypeInfo
{
    size_t size;
    char* name;
    size_t offset_len;
    size_t offsets[];
} TypeInfo;

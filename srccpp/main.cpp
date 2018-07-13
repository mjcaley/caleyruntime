#include <array>
#include <cstddef>
#include <iostream>


template <typename T, std::size_t N>
struct TypeInfo
{
    using type = T;
    std::size_t size { sizeof(T) };
    std::array<std::size_t, N> offsets;
};

struct Header
{
    const TypeInfo* metadata;
    int mark { 0 };

};

struct StackAllocation
{
    const TypeInfo* metadata;
    void* allocation;
};

struct HeapAllocation
{
    int mark;
    const TypeInfo* metadata;
    void* allocation;
};

template<typename T>
struct Value : public Header
{
    using type = T;

    T value;
};

template<typename T>
struct Reference
{
    using type = T;

    T* value;
};


struct UserStruct
{
    static const std::array<std::size_t, 1> _offsets { offsetof(UserStruct, number) };

    int number;
};

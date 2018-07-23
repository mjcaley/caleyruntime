#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


// template <typename T, std::size_t N>
// struct TypeInfo
// {
//     using type = T;
//     std::size_t size { sizeof(T) };
//     std::array<std::size_t, N> offsets;
// };

// struct Header
// {
//     const TypeInfo* metadata;
//     int mark { 0 };

// };

// struct StackAllocation
// {
//     const TypeInfo* metadata;
//     void* allocation;
// };

// struct HeapAllocation
// {
//     int mark;
//     const TypeInfo* metadata;
//     void* allocation;
// };

// template<typename T>
// struct Value : public Header
// {
//     using type = T;

//     T value;
// };

// template<typename T>
// struct Reference
// {
//     using type = T;

//     T* value;
// };




// struct UserStruct
// {
//     static const std::array<std::size_t, 1> _offsets { offsetof(UserStruct, number) };

//     int number;
// };



// String literal template parameter?
template<char ... Chars>
struct String
{
    static constexpr char const data[sizeof...(Chars) + 1] = { Chars..., '\0' };
    static constexpr std::size_t size() { return sizeof...(Chars); }
};



// // template<typename std::size_t N>
// // constexpr char get_char(const char (&input)[N], std::size_t index)
// // {
// //     return input[index];
// // }
// constexpr const char get_char(const char *const input[], std::size_t index)
// {
//     return input[index];
// }

// template<std::size_t N, std::size_t ... Index>
// constexpr auto char_array(const char (&char_array_input)[N], std::index_sequence<Index...>)
// {
//     // String<*(&char_array_input + Index)...> s;
//     String<get_char(char_array_input, Index)...> s;
//     return s;
// }

// template<std::size_t N>
// constexpr auto from_string(const char (&string)[N])
// {
//     using length = std::make_index_sequence<N>;
//     auto new_string = char_array(string, length{});

//     return new_string;
// }



// Single template, type aliases

// template<typename T, char const *const Name, std::size_t... Offsets>
// struct TypeDesc
// {
//     using type = T;

//     const std::size_t size { sizeof(T) };
//     char const *const name { Name };
//     const std::array<std::size_t, sizeof...(Offsets)> offsets { Offsets... };
// };

// template<typename T, const TypeDesc<T>* Tag>
// struct Object
// {
//     const TypeTag<T>* type_tag { Tag };
//     T data;
// };

// const TypeDesc<int32_t> i32_def = {

// };


template<typename T, const char* Name, std::size_t... Offsets>
struct TypeDescription
{
    using type = T;

    static constexpr const std::size_t size { sizeof(type) };
    static constexpr const char* name { Name };
    static constexpr const std::array<std::size_t, sizeof...(Offsets)> offsets { Offsets... };
};

using i32_def = TypeDescription<int, String<'i', 'n', 't'>::data>;


template<typename T>
std::add_pointer_t<typename T::type> allocate()
{
    void* ptr = std::malloc(T::size);

    return static_cast<std::add_pointer_t<typename T::type>>(ptr);
};

int main()
{
    std::cout << String<'A', ' ' , 's', 't', 'r', 'i', 'n', 'g'>::data << std::endl;

    // std::cout << from_string("A").string << std::endl;

    

    std::cout << "Type description name:" << i32_def::name << std::endl;

    return 0;
};

#ifndef SHIVLIB_STRING_VIEW_HPP
#define SHIVLIB_STRING_VIEW_HPP

#include <iterator>

namespace ShivLib{
    template<typename T>
    class string_view{
        using value_type = T;
        using pointer = T*;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<T*>;
        using const_reverse_iterator = const std::reverse_iterator<const T*>;
        using reference = T&;
        using const_reference = const T&;
        using rvalue_reference = T&&;




    };
}


#endif//SHIVLIB_STRING_VIEW_HPP

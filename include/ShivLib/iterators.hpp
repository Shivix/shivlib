#ifndef SHIVLIB_ITERATORS_HPP
#define SHIVLIB_ITERATORS_HPP

#include "cstddef.hpp"

namespace ShivLib{
    template<typename category, typename T>
    struct iterator_traits{
        using iterator_category = category;
        using value_type = T; // the type the iterator points to
        using difference_type = ptrdiff_t; // distance between operators
        using pointer = T*;
        using reference = T&;
    };

    template<typename category, typename T>
    struct iterator_traits<category, const T*>{
        using iterator_category = category;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
    };
    
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

    template<typename T>
    class reverse_iterator: public iterator_traits<random_access_iterator_tag, T>{
        
        
        
        
        
    };
    
    
}

#endif //SHIVLIB_ITERATORS_HPP

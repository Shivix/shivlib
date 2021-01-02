#ifndef SHIVLIB_ITERATORS_HPP
#define SHIVLIB_ITERATORS_HPP

#include "cstddef.hpp"
#include "type_traits.hpp"

namespace shiv {
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
class reverse_iterator: public iterator_traits<random_access_iterator_tag, remove_pr_t<T>>{

        T baseIterator;
    public:
        
        using traits_type = iterator_traits<random_access_iterator_tag, T>;
        using pointer = typename traits_type::pointer;
        using reference = typename traits_type::reference;
        using difference_type = typename traits_type::difference_type;
        
        reverse_iterator():
        baseIterator(){}
        
        explicit constexpr
        reverse_iterator(T input):
        baseIterator(input){}
        
        constexpr 
        reverse_iterator(const reverse_iterator& input):
        baseIterator(input.baseIterator){}
        reverse_iterator& operator= (const reverse_iterator&) = default;

        template<typename inputT>
        constexpr
        reverse_iterator(const reverse_iterator<inputT>& input): // can copy to an iterator of different type if the pointed to type can be converted
        baseIterator(input.getBase()){}
        
        constexpr T
        getBase() const{
            return baseIterator;
        }
        
        // dereference operators
        constexpr reference
        operator* () const{
            T temporary = baseIterator;
            return *--temporary;
        }
        
        constexpr pointer 
        operator-> () const{
            T temporary = baseIterator;
            return --temporary;
        }
        
        // increment/ decrement
        constexpr reverse_iterator&
        operator++ (){ // pre-increment operator
            --baseIterator;
            return *this;
        }
        constexpr reverse_iterator
        operator++ (int){ // post-increment operator
            reverse_iterator temporary = *this;
            --baseIterator;
            return temporary;
        }

        constexpr reverse_iterator&
        operator-- (){ // pre-increment operator
            ++baseIterator;
            return *this;
        }
        constexpr reverse_iterator
        operator-- (int){ // post-increment operator
            reverse_iterator temporary = *this;
            ++baseIterator;
            return temporary;
        }
        
        constexpr auto
        operator+ (difference_type scalar) const{
            return reverse_iterator(baseIterator - scalar);
        }
        constexpr reverse_iterator&
        operator+= (difference_type scalar){
            baseIterator -= scalar;
            return *this;
        }

        constexpr auto
        operator- (difference_type scalar) const{
            return reverse_iterator(baseIterator + scalar);
        }
        constexpr reverse_iterator&
        operator-= (difference_type scalar){
            baseIterator += scalar;
            return *this;
        }
        
        constexpr reference
        operator[] (difference_type index) const{
            return *(*this + index);
        }
        
        // comparison operators
        constexpr bool
        operator== (const reverse_iterator& other) const{
            return baseIterator == other.baseIterator;
        }
        constexpr bool
        operator!= (const reverse_iterator& other) const{
            return baseIterator != other.baseIterator;
        }

        constexpr bool
        operator> (const reverse_iterator& other) const{
            return baseIterator > other.baseIterator;
        }
        constexpr bool
        operator< (const reverse_iterator& other) const{
            return baseIterator < other.baseIterator;
        }
        constexpr bool
        operator>= (const reverse_iterator& other) const{
            return baseIterator >= other.baseIterator;
        }
        constexpr bool
        operator<= (const reverse_iterator& other) const{
            return baseIterator <= other.baseIterator;
        }
    };
    template<typename iter>
    inline constexpr reverse_iterator<iter>
    make_reverse_iterator(iter input){
        return reverse_iterator<iter>(input);
    }
}

#endif //SHIVLIB_ITERATORS_HPP

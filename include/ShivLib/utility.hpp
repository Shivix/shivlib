#ifndef SHIVLIB_UTILITY_HPP
#define SHIVLIB_UTILITY_HPP

#include "typeTraits.hpp"

namespace ShivLib{
    template<typename T>
    constexpr T&& 
    move(T&& input) noexcept { // casts a value to an rvalue to allow move semantics and other features.
        return static_cast<typename ShivLib::remove_reference<T>::type&&>(input);
    }
    
    template<typename T>
    constexpr T&&
    forward(typename ShivLib::remove_reference<T>::type& input) noexcept {
        return static_cast<T&&>(input);
    }
    template<typename T>
    constexpr T&& // lvalues will cannot be perfectly forwarded, so to make the behaviour explicit this function will be used and will assert at compile time
    forward(typename ShivLib::remove_reference<T>::type&& input) noexcept {
        static_assert(!ShivLib::is_lvalue_reference<T>(), "Must forward an rvalue");
        return static_cast<T&&>(input);
    }
}


#endif //SHIVLIB_UTILITY_HPP

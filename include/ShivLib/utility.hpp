#ifndef SHIVLIB_UTILITY_HPP
#define SHIVLIB_UTILITY_HPP

#include "type_traits.hpp"

namespace shiv {
    template<typename T>
    constexpr inline T&& 
    move(T&& input) noexcept { // casts a value to an rvalue to allow move semantics and other features.
        return static_cast<typename shiv::remove_reference<T>::type&&>(input);
    }
    
    template<typename T>
    constexpr inline T&&
    forward(typename shiv::remove_reference<T>::type& input) noexcept {
        return static_cast<T&&>(input);
    }
    template<typename T>
    constexpr inline T&& // lvalues will cannot be perfectly forwarded, so to make the behaviour explicit this function will be used and will assert at compile time
    forward(typename shiv::remove_reference<T>::type&& input) noexcept {
        static_assert(!shiv::is_lvalue_reference<T>(), "Must forward an rvalue");
        return static_cast<T&&>(input);
    }
}


#endif //SHIVLIB_UTILITY_HPP

#ifndef SHIVLIB_UTILITY_HPP
#define SHIVLIB_UTILITY_HPP

#include "typeTraits.hpp"

namespace ShivLib{
    template<typename T>
    constexpr auto 
    move(T&& input) noexcept {
        return static_cast<typename ShivLib::remove_reference<T>::type&&>(input);
    }
    
    template<typename T>
    constexpr T&&
    forward(typename ShivLib::remove_reference<T>::type& input) noexcept {
        return static_cast<T&&>(input);
    }
    template<typename T>
    constexpr T&&
    forward(typename ShivLib::remove_reference<T>::type&& input) noexcept {
        static_assert(!ShivLib::is_lvalue_reference<T>::check, "Must forward an rvalue");
        return static_cast<T&&>(input);
    }
}


#endif //SHIVLIB_UTILITY_HPP

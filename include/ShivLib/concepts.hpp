#ifndef SHIVLIB_CONCEPTS_HPP
#define SHIVLIB_CONCEPTS_HPP

#include "type_traits.hpp"

namespace shiv{
    template<typename T>
    concept integral = shiv::is_integral_v<T>;
    template<typename T>
    concept floatingPoint = shiv::is_floating_point_v<T>;
    template<typename T>
    concept arithmetic = shiv::is_arithmetic_v<T>;
}

#endif//SHIVLIB_CONCEPTS_HPP

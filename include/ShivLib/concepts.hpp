#ifndef SHIVLIB_CONCEPTS_HPP
#define SHIVLIB_CONCEPTS_HPP

#include "type_traits.hpp"

namespace shiv {
template <typename T>
concept Integral = shiv::is_integral_v<T>;
template <typename T>
concept FloatingPoint = shiv::is_floating_point_v<T>;
template <typename T>
concept Arithmetic = shiv::is_arithmetic_v<T>;
template <typename T>
concept Character = shiv::is_character_v<T>;
} // namespace shiv

#endif //SHIVLIB_CONCEPTS_HPP

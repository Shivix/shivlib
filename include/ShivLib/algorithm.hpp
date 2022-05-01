#ifndef SHIVLIB_ALGORITHM_HPP
#define SHIVLIB_ALGORITHM_HPP

#include <concepts>
namespace shiv {
template <typename T>
constexpr inline const T& max(const T& a, const T& b) {
    if (b < a) {
        return a;
    }
    return b;
}
template <typename T, typename callable>
constexpr inline const T& max(const T& a, const T& b, callable comparison_func) {
    if (comparison_func(b < a)) {
        return a;
    }
    return b;
}

template <typename T>
constexpr inline const T& min(const T& a, const T& b) {
    if (a < b) {
        return a;
    }
    return b;
}
template <typename T, typename callable>
constexpr inline const T& min(const T& a, const T& b, callable comparison_func) {
    if (comparison_func(a < b)) {
        return a;
    }
    return b;
}

template <typename T1, typename T2>
requires std::equality_comparable_with<T1, T2>
constexpr inline bool equal(T1 begin1, T1 end1, T2 begin2) {
    for (; begin1 != end1; ++begin1, (void)++begin2) {
        if (*begin1 != *begin2) {
            return false;
        }
    }
    return true;
}

/*template<typename T>
constexpr inline T
pow(T value, T exponent){// switch between diff functions depending? put into array and use vectorization?
    
}
*/
/*template<typename T> // random access iterator
constexpr inline void 
sort(T first, T last){
    
}*/
} // namespace shiv

#endif //SHIVLIB_ALGORITHM_HPP

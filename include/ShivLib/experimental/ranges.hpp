#ifndef SHIVLIB_RANGES_HPP
#define SHIVLIB_RANGES_HPP

#include <cstddef>
#include <vector>

template <typename T> //gd
struct range {
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    //using reverse_iterator = std::reverse_iterator<T*>;
    //using const_reverse_iterator = const std::reverse_iterator<const T*>;
    using reference = T&;
    using const_reference = const T&;

    range(T begin, T end) {
        data.resize(end - begin);
        for (auto&& i : data) {
            i = begin++;
        }
    }
    std::vector<T> data;

    constexpr T* begin() noexcept {
        return data.data();
    }
    constexpr T* end() noexcept {
        return data.data() + data.size();
    }
};

#endif //SHIVLIB_RANGES_HPP

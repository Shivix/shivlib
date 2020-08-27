#ifndef SHIVLIB_ARRAY_HPP
#define SHIVLIB_ARRAY_HPP


#include <iterator>

namespace ShivLib{
    template<typename T, std::size_t size>
    class array{
    public:
        using value_type = T;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<T*>;
        using const_reverse_iterator = const std::reverse_iterator<const T*>;
        using reference = T&;
        using const_reference = const T&;

        T m_data[size];
        constexpr T* 
        data() noexcept{
            return m_data;
        }
        // Iterators
        constexpr auto
        begin() noexcept{
            return iterator(data());
        }
        constexpr auto 
        begin() const noexcept{
            return const_iterator(data());
        }
        constexpr auto 
        cbegin() const noexcept{
            return const_iterator(data());
        }
        constexpr auto
        rbegin() noexcept{
            return reverse_iterator(data());
        }
        constexpr auto
        rbegin() const noexcept{
            return const_reverse_iterator(data());
        }
        constexpr auto
        crbegin() const noexcept{
            return const_reverse_iterator(data());
        }
        constexpr auto
        end() noexcept{
            return iterator(data() + size);
        }
        constexpr auto
        end() const noexcept{
            return const_iterator(data() + size);
        }
        constexpr auto
        cend() const noexcept{
            return const_iterator(data() + size);
        }
        constexpr auto
        rend() noexcept{
            return reverse_iterator(data() + size);
        }
        constexpr auto
        rend() const noexcept{
            return const_reverse_iterator(data() + size);
        }
        constexpr auto
        crend() const noexcept{
            return const_reverse_iterator(data() + size);
        }

        // Capacity

    };
}



#endif //SHIVLIB_ARRAY_HPP

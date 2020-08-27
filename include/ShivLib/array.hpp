#ifndef SHIVLIB_ARRAY_HPP
#define SHIVLIB_ARRAY_HPP


#include <iterator>

namespace ShivLib{
    template<typename T, std::size_t numOfElems>
    class array{
    public:
        using value_type = T;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<T*>;
        using const_reverse_iterator = const std::reverse_iterator<const T*>;
        using reference = T&;
        using const_reference = const T&;

        T m_data[numOfElems];
        
        constexpr T* 
        data() noexcept{
            return m_data;
        }
        constexpr const T*
        data() const noexcept{
            return m_data;
        }
        
        void 
        fill(const value_type& input){
            std::fill(begin(), end(), input);
        }
        
        void 
        swap(array other) noexcept{
            std::swap_ranges(begin(), end(), other.begin());
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
            return iterator(data() + numOfElems);
        }
        constexpr auto
        end() const noexcept{
            return const_iterator(data() + numOfElems);
        }
        constexpr auto
        cend() const noexcept{
            return const_iterator(data() + numOfElems);
        }
        constexpr auto
        rend() noexcept{
            return reverse_iterator(data() + numOfElems);
        }
        constexpr auto
        rend() const noexcept{
            return const_reverse_iterator(data() + numOfElems);
        }
        constexpr auto
        crend() const noexcept{
            return const_reverse_iterator(data() + numOfElems);
        }

        // Capacity
        [[nodiscard]] constexpr std::size_t
        size() const noexcept{
            return numOfElems;
        }
        [[nodiscard]] constexpr bool 
        empty() const noexcept{
            return size() == 0;
        }
        
        // Comparison
        constexpr bool 
        operator == (const array& other) const{
            return std::equal(begin(), end(), other.begin());
        }
        constexpr bool
        operator != (const array& other) const{
            return !(this == other);
        }
    };
}



#endif //SHIVLIB_ARRAY_HPP

#ifndef SHIVLIB_ARRAY_HPP
#define SHIVLIB_ARRAY_HPP

#include <iterator>
#include <cassert>

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
        
        T elems[numOfElems];
        
        constexpr T* 
        data() noexcept{
            return elems;
        }
        constexpr const T*
        data() const noexcept{
            return elems;
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
        
        // Element Access
        constexpr reference 
        operator [] (std::size_t index) noexcept{
            assert((index < numOfElems)&&("Index out of range"));
            return elems[index];
        }
        constexpr const_reference
        operator [] (std::size_t index) const noexcept{
            assert((index < numOfElems)&&("Index out of range"));
            return elems[index];
        }
        
        constexpr reference 
        at(std::size_t index){
            if(index >= numOfElems){
                throw std::out_of_range("Element out of range");
            }
            else{
                return elems[index];
            }
        }
        constexpr const_reference
        at(std::size_t index) const{
            if(index >= numOfElems){
                throw std::out_of_range("Element out of range");
            }
            else{
                return elems[index];
            }
        }

        // Capacity
        [[nodiscard]] constexpr std::size_t
        size() const noexcept{
            return numOfElems;
        }
        [[nodiscard]] constexpr std::size_t
        max_size() const noexcept{
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
    
    template<typename T>
    class array<T, 0>{ // allows the creation of size 0 arrays
        
    };
}



#endif //SHIVLIB_ARRAY_HPP

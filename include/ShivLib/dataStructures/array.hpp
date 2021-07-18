#ifndef SHIVLIB_ARRAY_HPP
#define SHIVLIB_ARRAY_HPP

#include "../cstddef.hpp"
#include <cassert>
#include <iterator>

namespace shiv {
template<typename T, size_t num_of_elems>
struct array{ // all public with no constuctor for aggregate initialization
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<T*>;
    using const_reverse_iterator = const std::reverse_iterator<const T*>;
    using reference = T&;
    using const_reference = const T&;
    
    T elems[num_of_elems]; // NOLINT

    [[nodiscard]] constexpr T* 
    data() noexcept{
        return elems;
    }
    [[nodiscard]] constexpr const T*
    data() const noexcept{
        return elems;
    }

    constexpr void
    fill(const value_type& input){
        std::fill(begin(), end(), input);
    }

    constexpr void
    swap(array& other) noexcept{
        std::swap_ranges(begin(), end(), other.begin());
    }
    
    // Iterators
    [[nodiscard]] constexpr auto
    begin() noexcept{
        return iterator(elems);
    }
    [[nodiscard]] constexpr auto 
    begin() const noexcept{
        return const_iterator(elems);
    }
    [[nodiscard]] constexpr auto 
    cbegin() const noexcept{
        return const_iterator(elems);
    }
    [[nodiscard]] constexpr auto
    rbegin() noexcept{
        return reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto
    rbegin() const noexcept{
        return const_reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto
    crbegin() const noexcept{
        return const_reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto
    end() noexcept{
        return iterator(elems + num_of_elems);
    }
    [[nodiscard]] constexpr auto
    end() const noexcept{
        return const_iterator(elems + num_of_elems);
    }
    [[nodiscard]] constexpr auto
    cend() const noexcept{
        return const_iterator(elems + num_of_elems);
    }
    [[nodiscard]] constexpr auto
    rend() noexcept{
        return reverse_iterator(begin());
    }
    [[nodiscard]] constexpr auto
    rend() const noexcept{
        return const_reverse_iterator(begin());
    }
    [[nodiscard]] constexpr auto
    crend() const noexcept{
        return const_reverse_iterator(begin());
    }
    
    // Element Access
    [[nodiscard]] constexpr reference 
    operator [] (size_t index) noexcept{
        return elems[index];
    }
    [[nodiscard]] constexpr const_reference
    operator [] (size_t index) const noexcept{
        return elems[index];
    }

    [[nodiscard]] constexpr reference 
    at(size_t index){
        if(index >= num_of_elems){
            throw std::out_of_range("Element out of range");
        }
        return elems[index];
    }
    [[nodiscard]] constexpr const_reference
    at(size_t index) const{
        if(index >= num_of_elems){
            throw std::out_of_range("Element out of range");
        }
        return elems[index];
    }

    [[nodiscard]] constexpr reference
    front() noexcept{
        return *begin();
    }
    [[nodiscard]] constexpr const_reference
    front() const noexcept{
        return *begin();
    }

    [[nodiscard]] constexpr reference
    back() noexcept{
        return *(end() - 1);
    }
    [[nodiscard]] constexpr const_reference
    back() const noexcept{
        return *(end() - 1);
    }

    // Capacity
    [[nodiscard]] constexpr size_t
    size() const noexcept{
        return num_of_elems;
    }
    [[nodiscard]] constexpr size_t
    max_size() const noexcept{
        return num_of_elems;
    }
    [[nodiscard]] constexpr bool 
    empty() const noexcept{
        return size() == 0;
    }
    
    // Comparison
    [[nodiscard]] constexpr bool 
    friend operator == (const array& lhs, const array& rhs){
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    [[nodiscard]] constexpr std::partial_ordering
    friend operator <=> (const array& lhs, const array& rhs){
        for(size_t i{0}; i < num_of_elems; ++i){
            auto comp_result{lhs[i] <=> rhs[i]};
            if (comp_result != std::strong_ordering::equal){
                return comp_result;
            }
        }
        return std::strong_ordering::equal;
    }
    
    // Assignment
    template<typename T2, std::size_t num_of_elems_2>
    constexpr array& 
    operator = (const array<T2, num_of_elems_2>& other){
        std::copy(other.begin(), other.end(), begin());
        return *this;
    }
};

template<typename T>
class array<T, 0>{ // allows the creation of size 0 arrays
public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<T*>;
    using const_reverse_iterator = const std::reverse_iterator<const T*>;
    using reference = T&;
    using const_reference = const T&;

    [[nodiscard]] constexpr T*
    data() noexcept{
        return 0;
    }
    [[nodiscard]] constexpr const T*
    data() const noexcept{
        return 0;
    }

    constexpr void
    fill(const value_type&){
    }

    constexpr void
    swap(array&) noexcept{
    }

    // Iterators
    [[nodiscard]] constexpr auto
    begin() noexcept{
        return iterator(this);
    }
    [[nodiscard]] constexpr auto
    begin() const noexcept{
        return const_iterator(this);
    }
    [[nodiscard]] constexpr auto
    cbegin() const noexcept{
        return const_iterator(this);
    }
    [[nodiscard]] constexpr auto
    rbegin() noexcept{
        return reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto
    rbegin() const noexcept{
        return const_reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto
    crbegin() const noexcept{
        return const_reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto
    end() noexcept{
        return iterator(this);
    }
    [[nodiscard]] constexpr auto
    end() const noexcept{
        return const_iterator(this);
    }
    [[nodiscard]] constexpr auto
    cend() const noexcept{
        return const_iterator(this);
    }
    [[nodiscard]] constexpr auto
    rend() noexcept{
        return reverse_iterator(begin());
    }
    [[nodiscard]] constexpr auto
    rend() const noexcept{
        return const_reverse_iterator(begin());
    }
    [[nodiscard]] constexpr auto
    crend() const noexcept{
        return const_reverse_iterator(begin());
    }

    // Element Access
    [[nodiscard]] constexpr reference
    operator [] (const size_t& i) noexcept{
        assert(!"Zero sized array");
        return reference(i);
    }
    [[nodiscard]] constexpr const_reference
    operator [] (size_t) const noexcept{
        assert(!"Zero sized array");
    }

    [[nodiscard]] constexpr reference
    at(size_t){
        throw std::out_of_range("Accessed a zero sized array");
    }
    [[nodiscard]] constexpr const_reference
    at(size_t) const{
        throw std::out_of_range("Accessed a zero sized array");
    }

    [[nodiscard]] constexpr reference
    front() {
        throw std::out_of_range("Accessed a zero sized array");
    }
    [[nodiscard]] constexpr const_reference
    front() const{
        throw std::out_of_range("Accessed a zero sized array");
    }

    [[nodiscard]] constexpr reference
    back() {
        throw std::out_of_range("Accessed a zero sized array");
    }
    [[nodiscard]] constexpr const_reference
    back() const{
        throw std::out_of_range("Accessed a zero sized array");
    }

    // Capacity
    [[nodiscard]] constexpr size_t
    size() const noexcept{
        return 0;
    }
    [[nodiscard]] constexpr size_t
    max_size() const noexcept{
        return 0;
    }
    [[nodiscard]] constexpr bool
    empty() const noexcept{
        return true;
    }

    // Comparison
    [[nodiscard]] friend constexpr bool
    operator == (const array& lhs, const array& rhs){
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    [[nodiscard]] friend constexpr bool
    operator != (const array& lhs, const array& rhs){
        return !(lhs == rhs);
    }

    // Assignment
    template<typename T2, size_t num_of_elems_2>
    constexpr array<T, 0>&
    operator = (const array<T2, num_of_elems_2>&){
        return *this;
    }
};
} // namespace shiv


#endif //SHIVLIB_ARRAY_HPP

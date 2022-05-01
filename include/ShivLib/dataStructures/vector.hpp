#ifndef SHIVLIB_VECTOR_HPP
#define SHIVLIB_VECTOR_HPP

#include "../cstddef.hpp"
#include "../type_traits.hpp"
#include "../utility.hpp"
#include <cassert>
#include <iterator>
#include <memory>

namespace shiv {
template <typename T, typename A = std::allocator<T>>
class Vector {
    using alloc = std::allocator_traits<A>;

  public:
    using value_type = T;
    using pointer = T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<T*>;
    using const_reverse_iterator = const std::reverse_iterator<const T*>;
    using reference = T&;
    using const_reference = const T&;
    using rvalue_reference = T&&;

    constexpr Vector() = default;

    constexpr explicit Vector(size_t capacity) {
        unsigned int rounded{1};
        while (capacity > rounded) {
            rounded <<= 1;
        }
        reallocate(rounded);
    }

    constexpr Vector(std::initializer_list<value_type> input)
    : Vector(input.size()) {
        for (int i{0}; auto&& elem : input) {
            m_data[i++] = elem;
        }
        m_size = input.size();
    }

    constexpr Vector(const Vector& other) {
        reallocate(other.m_capacity);
        for (int i{0}; auto&& elem : other) {
            m_data[i++] = elem;
        }
        m_size = other.size();
    }

    constexpr Vector& operator=(const Vector& other) {
        if (this != &other) {
            reallocate(other.m_capacity);
            for (int i{0}; auto&& elem : other) {
                m_data[i++] = elem;
            }
            m_size = other.m_size;
        }
        return *this;
    }

    constexpr Vector(Vector&& other) noexcept
    : m_data{std::exchange(other.m_data, nullptr)}
    , m_size{other.m_size}
    , m_capacity{other.m_capacity} {
    }

    constexpr Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            m_data = std::exchange(other.m_data, nullptr);
            m_size = other.m_size;
            m_capacity = other.m_capacity;
        }
        return *this;
    }

    constexpr ~Vector() {
        if (m_data != nullptr) {
            for (size_t i{0}; i < m_size; ++i) {
                alloc::destroy(allocator, &m_data[i]);
            }
            alloc::deallocate(allocator, m_data, m_capacity);
        }
    }

  private:
    pointer m_data{nullptr};
    A allocator;
    size_t m_size{0};
    size_t m_capacity{0};

    constexpr void reallocate(const size_t& new_capacity) {
        pointer new_data{alloc::allocate(allocator, new_capacity)};
        size_t new_size{m_size};
        if (new_capacity < m_size) {
            new_size = new_capacity;
        }
        for (size_t i{0}; i < new_size; ++i) {
            alloc::construct(allocator, &new_data[i], shiv::move_if_noexcept(m_data[i]));
        }
        if (m_data != nullptr) {
            for (size_t i{0}; i < m_size; ++i) {
                alloc::destroy(allocator, &m_data[i]);
            }
            alloc::deallocate(allocator, m_data, m_capacity);
        }
        m_data = new_data;
        m_size = new_size;
        m_capacity = new_capacity;
    }

  public:
    // adding elements
    constexpr void push_back(const_reference value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity * 2);
        }
        m_data[m_size] = value;
        ++m_size;
    }

    constexpr void push_back(rvalue_reference value) {
        emplace_back(shiv::move(value));
    }

    template <typename... args>
    constexpr reference emplace_back(args&&... values) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity * 2);
        }
        alloc::construct(allocator, &m_data[m_size], std::forward<args>(values)...);
        return m_data[m_size++];
    }

    template <typename... Args>
    constexpr iterator emplace(const_iterator position, Args&&... args) {
        ptrdiff_t distance{position - cbegin()};
        assert(position >= cbegin() && position <= cend());
        if (m_size >= m_capacity) {
            reallocate(m_capacity * 2);
        }
        std::move_backward(cbegin() + distance, cend(), end() + 1);
        m_data[distance] = shiv::move(T(shiv::forward<Args>(args)...));
        ++m_size;
        return iterator(cbegin() + distance);
    }

    constexpr iterator insert(const_iterator position, const T& value) {
        return emplace(position, value);
    }

    constexpr iterator insert(iterator position, size_t amount, const T& value) {
        ptrdiff_t distance{position - cbegin()};
        if (m_size + amount > m_capacity) {
            reallocate(m_capacity * 2);
        }
        std::move_backward(cbegin() + distance, cend(), end() + amount);
        m_size += amount;
        std::fill(begin() + distance, begin() + distance + amount, value);
        return iterator(cbegin() + distance);
    }

    constexpr iterator insert(const_iterator position,
                              std::initializer_list<value_type> value_list) {
        ptrdiff_t distance{position - cbegin()};
        assert(position >= cbegin() && position <= cend());
        if (m_size + value_list.size() > m_capacity) {
            reallocate(m_capacity * 2);
        }
        std::move_backward(cbegin() + distance, cend(), end() + value_list.size());
        m_size += value_list.size();
        for (iterator j{begin() + distance}; auto i : value_list) {
            *j = shiv::move(i);
            ++j;
        }
        return iterator(cbegin() + distance);
    }

    constexpr void reserve(const size_t& num_of_elems) {
        reallocate(num_of_elems);
    }

    constexpr void resize(const size_t& num_of_elems) {
        reallocate(num_of_elems);
    }

    // removing elements
    constexpr void pop_back() {
        if (m_size > 0) {
            --m_size;
            m_data[m_size].~value_type();
        }
    }

    constexpr void clear() {
        for (size_t i{0}; i < m_size; ++i) {
            m_data[i].~value_type();
        }
        m_size = 0;
    }

    constexpr void shrink_to_fit() {
        reallocate(m_size);
    }

    constexpr void fill(const value_type& input) {
        std::fill(begin(), end(), input);
    }

    constexpr void swap(Vector& other) noexcept {
        std::swap_ranges(begin(), end(), other.begin());
        std::swap(m_size, other.m_size);
    }

    // Element Access
    [[nodiscard]] constexpr reference operator[](size_t index) noexcept {
        return m_data[index];
    }
    [[nodiscard]] constexpr const_reference operator[](size_t index) const noexcept {
        return m_data[index];
    }

    [[nodiscard]] constexpr reference at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range{"Element out of range"};
        }
        return m_data[index];
    }
    [[nodiscard]] constexpr const_reference at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range{"Element out of range"};
        }
        return m_data[index];
    }

    [[nodiscard]] constexpr reference front() noexcept {
        return *begin();
    }
    [[nodiscard]] constexpr const_reference front() const noexcept {
        return *begin();
    }

    [[nodiscard]] constexpr reference back() noexcept {
        return *(end() - 1);
    }
    [[nodiscard]] constexpr const_reference back() const noexcept {
        return *(end() - 1);
    }

    // Iterators
    [[nodiscard]] constexpr auto begin() noexcept {
        return iterator{m_data};
    }

    [[nodiscard]] constexpr auto begin() const noexcept {
        return const_iterator{m_data};
    }

    [[nodiscard]] constexpr auto cbegin() const noexcept {
        return const_iterator{m_data};
    }

    [[nodiscard]] constexpr auto rbegin() noexcept {
        return reverse_iterator{end()};
    }

    [[nodiscard]] constexpr auto rbegin() const noexcept {
        return const_reverse_iterator{end()};
    }

    [[nodiscard]] constexpr auto crbegin() const noexcept {
        return const_reverse_iterator{end()};
    }

    [[nodiscard]] constexpr auto end() noexcept {
        return iterator{m_data + m_size};
    }

    [[nodiscard]] constexpr auto end() const noexcept {
        return const_iterator{m_data + m_size};
    }

    [[nodiscard]] constexpr auto cend() const noexcept {
        return const_iterator{m_data + m_size};
    }

    [[nodiscard]] constexpr auto rend() noexcept {
        return reverse_iterator{begin()};
    }

    [[nodiscard]] constexpr auto rend() const noexcept {
        return const_reverse_iterator{begin()};
    }

    [[nodiscard]] constexpr auto crend() const noexcept {
        return const_reverse_iterator{begin()};
    }

    // Capacity
    [[nodiscard]] constexpr size_t size() const noexcept {
        return m_size;
    }

    [[nodiscard]] constexpr size_t max_size() const noexcept {
        return m_capacity;
    }

    [[nodiscard]] constexpr size_t capacity() const noexcept {
        return m_capacity;
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return size() == 0;
    }

    // comparison
    [[nodiscard]] friend constexpr bool operator==(const Vector& lhs, const Vector& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    [[nodiscard]] friend constexpr std::partial_ordering operator<=>(const Vector& lhs,
                                                                     const Vector& rhs) {
        for (size_t i{0}; i < lhs.size(); ++i) {
            auto comp_result{lhs[i] <=> rhs[i]};
            if (comp_result != std::strong_ordering::equal) {
                return comp_result;
            }
        }
        return std::strong_ordering::equal;
    }
};

/*// Iterator class
template<class myVector>
class vector_iterator{
    using pointer = typename myVector::pointer;
    using const_iterator = typename myVector::const_iterator;
    using reference = typename myVector::reference;
    using const_reference = typename myVector::const_reference;

    pointer m_ptr;

public:
    constexpr vector_iterator& // pre-increment
    operator++(){
        ++m_ptr;
        return *this;
    }
    constexpr vector_iterator // post-increment
    operator++(int){
        const_iterator temp = *this;
        ++m_ptr;
        return temp;
    }
    constexpr vector_iterator& // pre-decrement
    operator--(){
        --m_ptr;
        return *this;
    }
    constexpr vector_iterator // post-decrement
    operator--(int){
        const_iterator temp = *this;
        --m_ptr;
        return temp;
    }

    // Element Access
    [[nodiscard]] constexpr reference
    operator[](size_t index) noexcept{
        return m_ptr + index;
    }

    [[nodiscard]] constexpr const_reference
    operator[](size_t index) const noexcept{
        return m_ptr + index;
    }
    
    constexpr pointer operator -> (){
        return m_ptr;
    }
    constexpr reference operator * (){
        return *m_ptr;
    }

    // comparison
    constexpr bool
    operator==(const vector_iterator& other) const{
        return m_ptr == other.m_ptr;
    }

    constexpr bool
    operator!=(const vector_iterator& other) const{
        return !(*this == other);
    }
};*/
} // namespace shiv

#endif //SHIVLIB_VECTOR_HPP

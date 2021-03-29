#ifndef SHIVLIB_VECTOR_HPP
#define SHIVLIB_VECTOR_HPP

#include "../cstddef.hpp"
#include "../type_traits.hpp"
#include <cassert>
#include <iterator>
#include <utility>
#include <bitset>
#include <bit>
#include <memory>

namespace shiv {
    template<typename T, typename A = std::allocator<T>>
    class vector{
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
        
        using alloc = std::allocator_traits<A>;
        
        constexpr vector() = default;
        
        constexpr explicit
        vector(size_t capacity){
            unsigned int rounded =1;
            while(capacity > rounded){
                rounded <<=1;
            }
            reallocate(rounded);
        }

        constexpr explicit
        vector(std::initializer_list<value_type> input):
        vector(input.size()){
            for(int i{0}; auto&& elem: input){
                m_data[i++] = elem;
            }
            m_size = input.size();
        }
        
        constexpr
        vector(const vector& other){
            reallocate(other.m_capacity);
            for(int i{0}; auto&& elem: other){
                m_data[i++] = elem;
            }
            m_size = other.size();
        }
        
        constexpr vector&
        operator=(const vector& other){
            if (this != &other){
                reallocate(other.m_capacity);
                for(int i{0}; auto&& elem: other){
                    m_data[i++] = elem;
                }
                m_size = other.m_size;
            }
            return *this;
        }

        constexpr
        vector(vector&& other):
            m_data{std::exchange(other.m_data, nullptr)},
            m_size{other.m_size},
            m_capacity{other.m_capacity} {}
        
        constexpr vector&
        operator=(vector&& other){
            if (this != &other){
                m_data = std::exchange(other.m_data, nullptr);
                m_size = other.m_size;
                m_capacity = other.m_capacity;
            }
            return *this;
        }

        constexpr
        ~vector(){
            for(size_t i = 0; i < m_size; ++i){
                m_data[i].~value_type();
            }
            if (m_data != nullptr){
                alloc::deallocate(allocator, m_data, m_capacity);
            }
        }

    private:

        pointer m_data{nullptr};
        A allocator{};
        size_t m_size{0};
        size_t m_capacity{0};

        constexpr void
        reallocate(const size_t& newCapacity){
            pointer newData = alloc::allocate(allocator, newCapacity);
            if(newCapacity < m_size){
                m_size = newCapacity;
            }
            if(m_size != 0){
                for(size_t i = 0; i < m_size; ++i){
                    new(&newData[i]) value_type(std::move(m_data[i]));
                } 
            }
            
            for(size_t i{0}; i < m_size; ++i){
                m_data[i].~value_type();
            }
            if(m_data != nullptr){
                alloc::deallocate(allocator, m_data, m_capacity);
            }
            m_data = newData;
            m_capacity = newCapacity;
        }

    public:
        // adding elements
        constexpr void
        push_back(const_reference value){
            if(m_size >= m_capacity){
                reallocate(m_capacity * 2);
            }
            m_data[m_size] = value;
            ++m_size;
        }
        
        constexpr void
        push_back(rvalue_reference value){
            emplace_back(std::move(value));
        }
        
        template<typename... args>
        constexpr reference
        emplace_back(args&& ... values){ // can avoid a copy/ move by creating the object in place
            if(m_size >= m_capacity){
                reallocate(m_capacity * 2);
            }
            new(&m_data[m_size]) value_type(std::forward<args>(values)...);

            return m_data[m_size++];
        }

        template<typename... Args>
        constexpr iterator
        emplace(const_iterator position, Args&&... args){
            shiv::ptrdiff_t distance{position - cbegin()};
            assert(position >= cbegin() && position <= cend());
            if(m_size >= m_capacity){
                reallocate(m_capacity * 2);
            }
            std::move_backward(cbegin() + distance, cend(), end() + 1);
            m_data[distance] = std::move(T(std::forward<Args>(args)...));
            ++m_size;
            return iterator(cbegin() + distance); 
        }

        constexpr iterator
        insert(const_iterator position, const T& value){
            return emplace(position, value);
        }
        
        constexpr iterator 
        insert(iterator position, size_t amount, const T& value){
            shiv::ptrdiff_t distance{position - cbegin()};
            if(m_size + amount > m_capacity){
                reallocate(m_capacity * 2);
            }
            std::move_backward(cbegin() + distance, cend(), end() + amount);
            m_size += amount;
            std::fill(begin() + distance, begin() + distance + amount, value);
            return iterator(cbegin() + distance);
        }
        
        constexpr iterator
        insert(const_iterator position, std::initializer_list<value_type> value_list){
            shiv::ptrdiff_t distance{position - cbegin()}; // if we reallocate memory, position will become invalid so we use distance instead
            assert(position >= cbegin() && position <= cend());
            if(m_size + value_list.size() > m_capacity){
                reallocate(m_capacity * 2);
            }
            std::move_backward(cbegin() + distance, cend(), end() + value_list.size());
            m_size += value_list.size();
            for(iterator j{begin() + distance}; auto i: value_list){
                *j = std::move(i);
                ++j;
            }
            return iterator(cbegin() + distance);
        }

        constexpr void
        reserve(const size_t& elemsToReserve){
            reallocate(elemsToReserve);
        }

        constexpr void
        resize(const size_t& elemsToResize){
            reallocate(elemsToResize);
        }

        // removing elements
        constexpr void
        pop_back(){
            if(m_size > 0){
                --m_size;
                m_data[m_size].~value_type();
            }
        }

        constexpr void
        clear(){
            for(size_t i{0}; i < m_size; ++i){
                m_data[i].~value_type();
            }
            m_size = 0;
        }
        
        constexpr void
        shrink_to_fit(){
            reallocate(m_size);
        }
        
        // swap & fill
        constexpr void
        fill(const value_type& input){
            std::fill(begin(), end(), input);
        }

        constexpr void
        swap(vector& other) noexcept{
            std::swap_ranges(begin(), end(), other.begin());
            std::swap(m_size, other.m_size);
        }

        // Element Access
        [[nodiscard]] constexpr reference
        operator[](size_t index) noexcept{
            assert((index < m_size) && ("Index out of range"));
            return m_data[index];
        }
        [[nodiscard]] constexpr const_reference
        operator[](size_t index) const noexcept{
            assert((index < m_size) && ("Index out of range"));
            return m_data[index];
        }

        constexpr reference
        at(size_t index){
            if(index >= m_size){
                throw std::out_of_range("Element out of range");
            }
            else{
                return m_data[index];
            }
        }
        constexpr const_reference
        at(size_t index) const{
            if(index >= m_size){
                throw std::out_of_range("Element out of range");
            }
            else{
                return m_data[index];
            }
        }

        constexpr reference
        front() noexcept{
            return *begin();
        }
        constexpr const_reference
        front() const noexcept{
            return *begin();
        }

        constexpr reference
        back() noexcept{
            return *(end() - 1);
        }
        constexpr const_reference
        back() const noexcept{
            return *(end() - 1);
        }

        // Iterators
        constexpr auto
        begin() noexcept{
            return iterator(m_data);
        }

        constexpr auto
        begin() const noexcept{
            return const_iterator(m_data);
        }

        constexpr auto
        cbegin() const noexcept{
            return const_iterator(m_data);
        }

        constexpr auto
        rbegin() noexcept{
            return reverse_iterator(end());
        }

        constexpr auto
        rbegin() const noexcept{
            return const_reverse_iterator(end());
        }

        constexpr auto
        crbegin() const noexcept{
            return const_reverse_iterator(end());
        }

        constexpr auto
        end() noexcept{
            return iterator(m_data + m_size);
        }

        constexpr auto
        end() const noexcept{
            return const_iterator(m_data + m_size);
        }

        constexpr auto
        cend() const noexcept{
            return const_iterator(m_data + m_size);
        }

        constexpr auto
        rend() noexcept{
            return reverse_iterator(begin());
        }

        constexpr auto
        rend() const noexcept{
            return const_reverse_iterator(begin());
        }

        constexpr auto
        crend() const noexcept{
            return const_reverse_iterator(begin());
        }

        // Capacity
        [[nodiscard]] constexpr size_t
        size() const noexcept{
            return m_size;
        }

        [[nodiscard]] constexpr size_t
        max_size() const noexcept{
            return m_capacity;
        }

        [[nodiscard]] constexpr size_t
        capacity() const noexcept{
            return m_capacity;
        }

        [[nodiscard]] constexpr bool
        empty() const noexcept{
            return size() == 0;
        }

        // comparison
        constexpr bool
        operator==(const vector& other) const{
            return std::equal(begin(), end(), other.begin());
        }

        constexpr bool
        operator!=(const vector& other) const{
            return !(*this == other);
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
}

#endif //SHIVLIB_VECTOR_HPP

#ifndef SHIVLIB_VECTOR_HPP
#define SHIVLIB_VECTOR_HPP

#include <iterator>
#include <cassert>
#include <memory>

namespace ShivLib{
    template<typename T>
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

        explicit vector(size_t capacity){
            reallocate(capacity);
        }

        vector(std::initializer_list<value_type> input){
            reallocate(input.size());
            int i = 0;
            for(auto&& elem: input){
                m_data[i++] = elem;
            }
            m_size = input.size();
        }

        ~vector(){
            for(size_t i = 0; i < m_size; ++i){
                m_data[i].~value_type();
            }
            ::operator delete(m_data, m_capacity * sizeof(value_type));
        }

    private:

        pointer m_data{nullptr};

        size_t m_size{0};
        size_t m_capacity{0};

        void
        reallocate(const size_t& newCapacity){
            auto newData = (pointer)::operator new(newCapacity * sizeof(value_type));

            if(newCapacity < m_size){
                m_size = newCapacity;
            }
            if(m_size != 0){
                for(size_t i = 0; i < m_size; ++i){
                    new(&newData[i]) value_type(std::move(m_data[i]));
                } 
            }
            
            for(size_t i = 0; i < m_size; ++i){
                m_data[i].~value_type();
            }

            ::operator delete(m_data, m_capacity * sizeof(value_type));
            m_data = newData;
            m_capacity = newCapacity;
        }

    public:
        // adding elements
        void
        push_back(reference value){
            if(m_size >= m_capacity){
                reallocate(m_capacity * 2);
            }
            m_data[m_size] = value;
            ++m_size;
        }

        template<typename... args>
        reference
        emplace_back(args&& ... values){ // can avoid a copy/ move by creating the object in place
            if(m_size >= m_capacity){
                reallocate(m_capacity * 2);
            }
            new(&m_data[m_size]) value_type(std::forward<args>(values)...);

            return m_data[m_size++];
        }

        void
        reserve(const size_t& elemsToReserve){
            reallocate(elemsToReserve);
        }

        void
        resize(const size_t& elemsToResize){
            reallocate(elemsToResize);
        }

        // removing elements
        void
        pop_back(){ // TODO: doesnt resize
            if(m_size > 0){
                --m_size;
                m_data[m_size].~value_type();
            }
        }

        void
        clear(){
            for(size_t i = 0; i < m_size; ++i){
                m_data[i].~value_type();
            }
            m_size = 0;
        }

        // swap & fill
        constexpr void
        fill(const value_type& input){
            std::fill(begin(), end(), input);
        }

        constexpr void
        swap(vector& other) noexcept{
            std::swap_ranges(begin(), end(), other.begin());
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

    // Iterator class
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
    };
}

#endif //SHIVLIB_VECTOR_HPP

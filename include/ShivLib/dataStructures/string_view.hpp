#ifndef SHIVLIB_STRING_VIEW_HPP
#define SHIVLIB_STRING_VIEW_HPP

#include "../concepts.hpp"
#include <cassert>
#include <iterator>

namespace shiv {
    template<shiv::character T = char> // character concept
    class string_view{
        const T* m_view;
        size_t m_length;
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

        static constexpr size_t npos = size_t(-1);

        constexpr string_view(): m_view{nullptr}, m_length{0} {}
        constexpr string_view(const T* view): m_view{view}/*, m_length{strlen(m_view)} */{
            int i{0};
            while (view[i] != T()){ // todo: test......???do for wide char too???
                ++i;
            }
            m_length = i;
        }
        constexpr string_view(const T* view, size_t count): m_view{view}, m_length{count} {}
        template<typename Begin, typename End> // TODO: concepts for iterators!!!!
        constexpr string_view(Begin begin, End end): m_view{begin}{
            m_length = end - begin; // todo: test
        }
        constexpr string_view(const std::string& str): string_view(str.data()) {} // TODO: change to shiv::string or add another?
        
        constexpr const_iterator
        data() const noexcept{
            return m_view;
        }

        constexpr void
        swap(string_view& other) noexcept{
            auto temp_view{m_view};
            auto temp_length{m_length};
            m_view = other.m_view;
            m_length = other.m_length;
            other.m_view = temp_view;
            other.m_length = temp_length;
        }
        
        // trim m_view
        constexpr void remove_prefix(size_t n){
            m_view += n;
            m_length -= n;
        }
        constexpr void remove_suffix(size_t n){
            m_length -= n;
        }

        // Iterators
        constexpr auto begin() const noexcept{
            return const_iterator(m_view);
        }
        constexpr auto cbegin() const noexcept{
            return const_iterator(m_view);
        }
        constexpr auto rbegin() const noexcept{
            return const_reverse_iterator(end());
        }
        constexpr auto crbegin() const noexcept{
            return const_reverse_iterator(end());
        }
        constexpr auto end() const noexcept{
            return const_iterator(m_view + m_length);
        }
        constexpr auto cend() const noexcept{
            return const_iterator(m_view + m_length);
        }
        constexpr auto rend() const noexcept{
            return const_reverse_iterator(begin());
        }
        constexpr auto crend() const noexcept{
            return const_reverse_iterator(begin());
        }

        // Element Access (read only)
        constexpr const_reference operator[] (size_t index) const noexcept{
            assert((index < m_length)&&("Index out of range"));
            return m_view[index];
        }

        constexpr const_reference at(size_t index) const{
            if(index >= m_length){
                throw std::out_of_range("Element out of range");
            }
            else{
                return m_view[index];
            }
        }

        constexpr const_reference front() const noexcept{
            return *begin();
        }

        constexpr const_reference back() const noexcept{
            return *(end() - 1);
        }

        [[nodiscard]] constexpr size_t size() const noexcept{
            return m_length;
        }
        [[nodiscard]] constexpr size_t length() const noexcept{
            return m_length;
        }
        [[nodiscard]] constexpr size_t max_size() const noexcept{
            return m_length;
        }
        [[nodiscard]] constexpr bool empty() const noexcept{
            return m_length == 0;
        }
        
        constexpr bool operator ==(const string_view& other) const noexcept{
            return std::equal(begin(), end(), other.begin());
        }
    };
}


#endif//SHIVLIB_STRING_VIEW_HPP

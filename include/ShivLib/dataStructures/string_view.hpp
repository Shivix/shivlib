#ifndef SHIVLIB_STRING_VIEW_HPP
#define SHIVLIB_STRING_VIEW_HPP

#include "../algorithm.hpp"
#include "../concepts.hpp"
#include <cassert>
#include <iterator>
#include <limits>

namespace shiv {

template <shiv::Character T = char>
class StringView {
    const T* m_view{nullptr};
    size_t m_length{};

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

    static constexpr size_t npos = size_t{static_cast<size_t>(-1)};

    constexpr StringView(const T* view)
    : m_view{view} /*, m_length{strlen(m_view)}*/ {
        int i{0};
        while (view[i] != T{}) {
            ++i;
        }
        m_length = i;
    }
    constexpr StringView(const T* view, size_t count)
    : m_view{view}
    , m_length{count} {
    }
    template <typename Begin, typename End> // TODO: concepts for iterators!!!!
    constexpr StringView(Begin begin, End end)
    : m_view{begin}
    , m_length{end - begin} {
    }
    constexpr StringView(const std::string& str)
    : StringView(str.data()) {
    }

    constexpr const_iterator data() const noexcept {
        return m_view;
    }

    constexpr void swap(StringView& other) noexcept {
        auto temp_view{m_view};
        auto temp_length{m_length};
        m_view = other.m_view;
        m_length = other.m_length;
        other.m_view = temp_view;
        other.m_length = temp_length;
    }

    constexpr StringView substr(size_t index, size_t n = npos) const noexcept {
        assert(index < m_length);
        n = shiv::min(n, length() - index);
        return StringView(m_view + index, n);
    }

    // trim m_view
    constexpr void remove_prefix(size_t n) {
        m_view += n;
        m_length -= n;
    }
    constexpr void remove_suffix(size_t n) {
        m_length -= n;
    }

    // comparison
    constexpr int compare(StringView view) const noexcept {
        size_t min_len{shiv::min(length(), view.length())};
        // loop through
        // -1 if lt
        for (size_t i{0}; i < min_len; ++i) {
            if ((*this)[i] < view[i]) {
                return (*this)[i] - view[i];
            }
            if ((*this)[i] > view[i]) {
                return (*this)[i] - view[i];
            }
        }
        return length() - view.length();
    }
    constexpr int compare(size_t pos1, size_t count1, StringView view, size_t pos2 = 0,
                          size_t count2 = npos) const noexcept {
        return substr(pos1, count1).compare(view.substr(pos2, count2));
    }

    // *_with
    constexpr bool starts_with(const StringView view) const noexcept {
        return substr(0, view.length()) == view;
    }
    constexpr bool starts_with(const T* str) const {
        return starts_with(StringView(str));
    }
    constexpr bool starts_with(T c) const noexcept {
        return !empty() && (front() == c);
    }

    constexpr bool ends_with(const StringView view) const noexcept {
        return size() >= view.size() && substr(length() - view.length(), view.length()) == view;
    }
    constexpr bool ends_with(const T* str) const {
        return ends_with(StringView(str));
    }
    constexpr bool ends_with(T c) const noexcept {
        return !empty() && (back() == c);
    }

    // Iterators
    [[nodiscard]] constexpr auto begin() const noexcept {
        return const_iterator(m_view);
    }
    [[nodiscard]] constexpr auto cbegin() const noexcept {
        return const_iterator(m_view);
    }
    [[nodiscard]] constexpr auto rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto crbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    [[nodiscard]] constexpr auto end() const noexcept {
        return const_iterator(m_view + m_length);
    }
    [[nodiscard]] constexpr auto cend() const noexcept {
        return const_iterator(m_view + m_length);
    }
    [[nodiscard]] constexpr auto rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    [[nodiscard]] constexpr auto crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    // Element Access (read only)
    [[nodiscard]] constexpr const_reference operator[](size_t index) const noexcept {
        assert((index < m_length) && ("Index out of range"));
        return m_view[index]; // NOLINT()
    }

    [[nodiscard]] constexpr const_reference at(size_t index) const {
        if (index >= m_length) {
            throw std::out_of_range("Element out of range");
        }
        return m_view[index];
    }

    [[nodiscard]] constexpr const_reference front() const noexcept {
        return *begin();
    }

    [[nodiscard]] constexpr const_reference back() const noexcept {
        return *(end() - 1);
    }

    [[nodiscard]] constexpr size_t size() const noexcept {
        return m_length;
    }
    [[nodiscard]] constexpr size_t length() const noexcept {
        return m_length;
    }
    [[nodiscard]] constexpr size_t max_size() const noexcept {
        return m_length;
    }
    [[nodiscard]] constexpr bool empty() const noexcept {
        return m_length == 0;
    }

    [[nodiscard]] friend constexpr bool operator==(const StringView& lhs,
                                                   const StringView& rhs) noexcept {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
};
} // namespace shiv

#endif //SHIVLIB_STRING_VIEW_HPP

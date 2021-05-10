#ifndef SHIVLIB_MATRIX_HPP
#define SHIVLIB_MATRIX_HPP

#include "array.hpp"
#include <tuple>
#include <cmath>
#include "../concepts.hpp"

namespace shiv {
    template<shiv::arithmetic T, size_t rows, size_t cols>
    class matrix{
    public:
        using value_type = T;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<T*>;
        using const_reverse_iterator = const std::reverse_iterator<const T*>;
        using reference = T&;
        using const_reference = const T&;
        
        // No explicit constructor/ destructor etc. for aggregate all members must also be public

        shiv::array<shiv::array<T, cols>, rows> m_data{}; // stores the matrix data
        
        [[nodiscard]] constexpr bool empty() const noexcept {
            return size() == 0;
        }
        constexpr void fill(const T& value){
            std::fill(begin(), end(), value);
        }
        [[nodiscard]] constexpr matrix<T, rows, cols * 2> get_augment(const matrix& other) const { // returns a matrix where the other matrix is "attached" to the original
            matrix<T, rows, cols * 2> result_matrix = {};
            
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < result_matrix[0].size(); ++j){
                    if(j >= cols){
                        result_matrix[i][j] = other[i][j - cols];
                    }
                    else{
                        result_matrix[i][j] = m_data[i][j];
                    }
                }
            }
            return result_matrix;
        }
        [[nodiscard]] constexpr T get_determinant() const {
            static_assert(rows == cols, "Must be a square matrix");
            T determinant = 1;
            if(rows == 1){
                return m_data[0][0];
            }
            else if(rows == 2){
                return (m_data[0][0] * m_data[1][1]) - (m_data[1][0] * m_data[0][1]);
            }
            else{
                const auto [row_echelon_form, is_negative] = get_row_echelon(); // row echelon is calculated first to reduce the complexity down closer to O(N^2)
                for(size_t i = 0; i < rows; ++i){ // determinate is the product of the main diagonal elements in a row echelon matrix
                    determinant *= row_echelon_form[i][i];
                }
                if(is_negative){
                    determinant = -determinant;
                }
            }
            return determinant;
        }
        [[nodiscard]] constexpr matrix get_identity() const {
            matrix identity_matrix = {};

            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    if(i == j){
                        identity_matrix[i][j] = 1;
                    }
                    else{
                        identity_matrix[i][j] = 0;
                    }
                }
            }
            return identity_matrix;
        }
        [[nodiscard]] constexpr matrix get_inverse() const {
            
            matrix<T, rows, cols * 2> aug_ident_matrix = get_augment(get_identity()); // gets the identity matrix and then augments it onto the original matrix
            
            const size_t AUG_ID_COLS = aug_ident_matrix[0].size(); // all arrays within the first have the same size
            
            // replace elements based on a constant scalar from ANOTHER row
            for(size_t i = 0; i < cols; ++i){
                for(size_t j = 0; j < rows; ++j){
                    if(i != j){
                        T scalar = aug_ident_matrix[j][i] / aug_ident_matrix[i][i];
                        for(size_t k = 0; k < AUG_ID_COLS; ++k){
                            aug_ident_matrix[j][k] -= aug_ident_matrix[i][k] * scalar;
                        } 
                    }
                }
            }
            // divide each row element by the diagonal elements that were skipped previously
            for (size_t i = 0; i < rows; i++) {
                T scalar = aug_ident_matrix[i][i];
                for (size_t j = 0; j < AUG_ID_COLS; j++) {
                    aug_ident_matrix[i][j] = aug_ident_matrix[i][j] / scalar;
                }
            }
            // add the inverted half of the augmented matrix to it's own matrix
            matrix inverted_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    inverted_matrix[i][j] = aug_ident_matrix[i][j + cols];
                }
            }
            return inverted_matrix;
        }
        [[nodiscard]] std::tuple<matrix, bool> get_row_echelon() const { // returns the row echelon form matrix so that the original is kept
            matrix result_matrix = *this;
            
            bool is_inverted = false; // keeps track of the sign of the determinant (before multiplication)

            for(size_t pivot_row = 0; (rows < cols ? pivot_row < rows - 1 : pivot_row < cols - 1); ++pivot_row){
                if(result_matrix[pivot_row][pivot_row] == 0){ 

                // swap pivot element with another non 0 element
                    size_t swap_row = pivot_row;
                    for(size_t i = pivot_row + 1; i < rows; i++){
                        if(result_matrix[i][pivot_row] != 0){
                            swap_row = i;
                            break;
                        }
                    }
                    if(swap_row == pivot_row){
                        continue;
                    }
                    is_inverted = !is_inverted;
                    // swaps the swap_row and pivot_row
                    result_matrix[swap_row].swap(result_matrix[pivot_row]);
                }
                // eliminate elements in x col under x col
                for(size_t target_row = pivot_row + 1; target_row < rows; ++target_row){
                    T scale = result_matrix[target_row][pivot_row] / result_matrix[pivot_row][pivot_row];
                    
                    for(size_t target_col = 0; target_col < cols; ++target_col){
                        result_matrix[target_row][target_col] -= scale * result_matrix[pivot_row][target_col];
                    }
                }
            }
            for(auto&& i: result_matrix){
                i = std::round(i * 1000) / 1000;
            }
            return std::make_tuple(result_matrix, is_inverted); // returns a tuple including the bool that keeps track of the sign 
        }                                                     // the tuple currently prevents the function from happening at compile time. Struct also prevents it.
        [[nodiscard]] constexpr matrix get_transpose() const {
            matrix<T, rows, cols> transposed_matrix = {}; // rows and cols are in opposite order for transposed matrix
            
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    transposed_matrix[i][j] = m_data[j][i];
                }
            }
            return transposed_matrix;
        }
        [[nodiscard]] constexpr bool is_orthogonal() const {
            return get_transpose() == get_inverse();
        }
        [[nodiscard]] constexpr size_t size() const noexcept{
            return rows * cols;
        }
        constexpr void swap(matrix& other) noexcept {
            for(size_t i = 0; i < rows; ++i){
                m_data[i].swap(other[i]);
            }
        }
        // Arithmetic operators 
        [[nodiscard]] friend constexpr matrix operator + (const matrix& lhs, const matrix& rhs) noexcept { 
            matrix<T, cols, rows> result_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){ // m_data[x] will all have same .size()
                    result_matrix[i][j] = lhs[i][j] + rhs[i][j];
                }
            }
            return result_matrix;
        }
        [[nodiscard]] constexpr matrix operator + (const T& scalar)const noexcept {
            matrix<T, cols, rows> result_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    result_matrix[i][j] = m_data[i][j] + scalar;
                }
            }
            return result_matrix;
        }
        [[nodiscard]] friend constexpr matrix operator - (const matrix& lhs, const matrix& rhs) noexcept {
            matrix<T, cols, rows> result_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){ // m_data[x] will all have same .size()
                    result_matrix[i][j] = lhs[i][j] - rhs[i][j];
                }
            }
            return result_matrix;
        }
        [[nodiscard]] constexpr matrix operator - (const T& scalar) const noexcept {
            matrix<T, cols, rows> result_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    result_matrix[i][j] = m_data[i][j] - scalar;
                }
            }
            return result_matrix;
        }
        template<std::size_t otherRows, std::size_t otherCols>
        [[nodiscard]] constexpr matrix operator * (const matrix<T, otherCols, otherRows>& other) const noexcept { 
            matrix<T, cols, otherRows> result_matrix = {};
            for(size_t i = 0; i < otherRows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    for(size_t k = 0; k < rows; ++k){
                        result_matrix[i][j] += m_data[i][k] * other[k][j];
                    }
                }
            }
            return result_matrix;
        }
        [[nodiscard]] constexpr matrix operator * (const T& scalar) const noexcept {
            matrix<T, cols, rows> result_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    result_matrix[i][j] = m_data[i][j] * scalar;
                }
            }
            return result_matrix;
        }
        template<size_t otherRows, size_t otherCols>
        [[nodiscard]] constexpr matrix operator / (matrix<T, otherCols, otherRows>& other) const noexcept {
            matrix inverted_matrix = other.get_inverse();
            return (*this * inverted_matrix);
        }
        [[nodiscard]] constexpr matrix operator / (const T& scalar) const noexcept {
            matrix<T, cols, rows> result_matrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    result_matrix[i][j] = m_data[i][j] / scalar;
                }
            }
            return result_matrix;
        }
        [[nodiscard]] friend constexpr matrix operator - (matrix& matrix) noexcept {
            for(auto&& i: matrix){
                i = -i;
            }
            return matrix;
        }
        // Arithmetic assignment operators
        friend constexpr matrix& operator += (matrix& lhs, const matrix& rhs) noexcept {
            lhs = lhs + rhs;
            return lhs;
        }
        constexpr matrix& operator += (const T& scalar) noexcept {
            *this = *this + scalar;
            return *this;
        }
        friend constexpr matrix& operator -= (matrix& lhs, const matrix& rhs) noexcept {
            lhs = lhs - rhs;
            return lhs;
        }
        constexpr matrix& operator -= (const T& scalar) noexcept {
            *this = *this - scalar;
            return *this;
        }
        template<std::size_t other_rows, std::size_t other_cols>
        constexpr matrix& operator *= (const matrix<T, other_cols, other_rows>& other) noexcept {
            *this = *this * other;
            return *this;
        }
        constexpr matrix& operator *= (const T& scalar) noexcept {
            *this = *this * scalar;
            return *this;
        }
        template<std::size_t other_rows, std::size_t other_cols>
        constexpr matrix& operator /= (const matrix<T, other_cols, other_rows>& other) noexcept {
            *this = *this / other;
            return *this;
        }
        constexpr matrix& operator /= (const T& scalar) noexcept {
            *this = *this / scalar;
            return *this;
        }
        // element access
        [[nodiscard]] constexpr shiv::array<T, cols>& operator [] (const size_t& index) noexcept {
            return m_data[index];
        }
        [[nodiscard]] constexpr const shiv::array<T, cols>& operator [] (const size_t& index) const noexcept {
            return m_data[index];
        }
        [[nodiscard]] constexpr reference at(size_t row_index, size_t col_index){
            if(row_index >= rows || col_index >= cols){
                throw std::out_of_range("Element out of range");
            }
            return m_data[row_index][col_index];
        }
        [[nodiscard]] constexpr const_reference at(size_t row_index, size_t col_index) const {
            if(row_index >= rows || col_index >= cols){
                throw std::out_of_range("Element out of range");
            }
            return m_data[row_index][col_index];
        }
        [[nodiscard]] constexpr iterator data() noexcept {
            return &m_data[0][0];
        }
        [[nodiscard]] constexpr const_iterator data() const noexcept { // if the data is const this function will be called instead
            return const_iterator(&m_data[0][0]);
        }
        [[nodiscard]] constexpr reference back() noexcept {
            return *(end() - 1);
        }
        [[nodiscard]] constexpr const_reference back() const noexcept {
            return *(end() - 1);
        }
        [[nodiscard]] constexpr reference front() noexcept {
            return *begin();
        }
        [[nodiscard]] constexpr const_reference front() const noexcept {
            return *begin();
        }
        // comparison operators
        [[nodiscard]] friend constexpr bool operator == (const matrix& lhs, const matrix& rhs) noexcept {
            for(size_t i = 0; i < rows; ++i){
                if(lhs[i] != rhs[i]){ // uses the shiv::array operator != overload and runs it for each column
                    return false;
                }
                else{
                    continue;
                }
            }
            return true;
        }
        [[nodiscard]] friend constexpr bool operator != (const matrix& lhs, const matrix& rhs) noexcept {
            return !(lhs == rhs);
        }
        // Iterators
        [[nodiscard]] constexpr auto begin() noexcept {
            return iterator(&m_data[0][0]);
        }
        [[nodiscard]] constexpr auto begin() const noexcept { // allows .begin to be used with a const matrix without ambiguity
            return const_iterator(&m_data[0][0]);
        }
        [[nodiscard]] constexpr auto cbegin() const noexcept {
            return const_iterator(&m_data[0][0]);
        }
        [[nodiscard]] constexpr auto rbegin() noexcept {
            return reverse_iterator(end());
        }
        [[nodiscard]] constexpr auto crbegin() const noexcept {
            return const_reverse_iterator(end());
        }
        [[nodiscard]] constexpr auto end() noexcept {
            return iterator(&m_data[rows - 1][cols - 1] + 1);
        }
        [[nodiscard]] constexpr auto end() const noexcept {
            return const_iterator(&m_data[rows - 1][cols - 1] + 1);
        }
        [[nodiscard]] constexpr auto cend() const noexcept {
            return const_iterator(&m_data[rows - 1][cols - 1] + 1);
        }
        [[nodiscard]] constexpr auto rend() noexcept {
            return reverse_iterator(begin());
        }
        [[nodiscard]] constexpr auto crend() const noexcept {
            return const_reverse_iterator(begin());
        }
    };
}

#endif //SHIVLIB_MATRIX_HPP

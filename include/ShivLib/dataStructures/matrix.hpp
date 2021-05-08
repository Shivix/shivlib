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
            matrix<T, rows, cols * 2> resultMatrix = {};
            
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < resultMatrix[0].size(); ++j){
                    if(j >= cols){
                        resultMatrix[i][j] = other[i][j - cols];
                    }
                    else{
                        resultMatrix[i][j] = m_data[i][j];
                    }
                }
            }
            return resultMatrix;
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
                const auto [rowEchelonFormMatrix, isNegative] = get_row_echelon(); // row echelon is calculated first to reduce the complexity down closer to O(N^2)
                for(size_t i = 0; i < rows; ++i){ // determinate is the product of the main diagonal elements in a row echelon matrix
                    determinant *= rowEchelonFormMatrix[i][i];
                }
                if(isNegative){
                    determinant = -determinant;
                }
            }
            return determinant;
        }
        [[nodiscard]] constexpr matrix get_identity() const {
            matrix identityMatrix = {};

            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    if(i == j){
                        identityMatrix[i][j] = 1;
                    }
                    else{
                        identityMatrix[i][j] = 0;
                    }
                }
            }
            return identityMatrix;
        }
        [[nodiscard]] constexpr matrix get_inverse() const {
            
            matrix<T, rows, cols * 2> augIdentMatrix = get_augment(get_identity()); // gets the identity matrix and then augments it onto the original matrix
            
            const size_t AUG_ID_COLS = augIdentMatrix[0].size(); // all arrays within the first have the same size
            
            // replace elements based on a constant scalar from ANOTHER row
            for(size_t i = 0; i < cols; ++i){
                for(size_t j = 0; j < rows; ++j){
                    if(i != j){
                        T scalar = augIdentMatrix[j][i] / augIdentMatrix[i][i];
                        for(size_t k = 0; k < AUG_ID_COLS; ++k){
                            augIdentMatrix[j][k] -= augIdentMatrix[i][k] * scalar;
                        } 
                    }
                }
            }
            // divide each row element by the diagonal elements that were skipped previously
            for (size_t i = 0; i < rows; i++) {
                T scalar = augIdentMatrix[i][i];
                for (size_t j = 0; j < AUG_ID_COLS; j++) {
                    augIdentMatrix[i][j] = augIdentMatrix[i][j] / scalar;
                }
            }
            // add the inverted half of the augmented matrix to it's own matrix
            matrix invertedMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    invertedMatrix[i][j] = augIdentMatrix[i][j + cols];
                }
            }
            return invertedMatrix;
        }
        [[nodiscard]] std::tuple<matrix, bool> get_row_echelon() const { // returns the row echelon form matrix so that the original is kept
            matrix resultMatrix = *this;
            
            bool isInverted = false; // keeps track of the sign of the determinant (before multiplication)

            for(size_t pivotRow = 0; (rows < cols ? pivotRow < rows - 1 : pivotRow < cols - 1); ++pivotRow){
                if(resultMatrix[pivotRow][pivotRow] == 0){ 

                // swap pivot element with another non 0 element
                    size_t swapRow = pivotRow;
                    for(size_t i = pivotRow + 1; i < rows; i++){
                        if(resultMatrix[i][pivotRow] != 0){
                            swapRow = i;
                            break;
                        }
                    }
                    if(swapRow == pivotRow){
                        continue;
                    }
                    isInverted = !isInverted;
                    // swaps the swapRow and pivotRow
                    resultMatrix[swapRow].swap(resultMatrix[pivotRow]);
                }
                // eliminate elements in x col under x col
                for(size_t targetRow = pivotRow + 1; targetRow < rows; ++targetRow){
                    T scale = resultMatrix[targetRow][pivotRow] / resultMatrix[pivotRow][pivotRow];
                    
                    for(size_t targetCol = 0; targetCol < cols; ++targetCol){
                        resultMatrix[targetRow][targetCol] -= scale * resultMatrix[pivotRow][targetCol];
                    }
                }
            }
            for(auto&& i: resultMatrix){
                i = std::round(i * 1000) / 1000;
            }
            return std::make_tuple(resultMatrix, isInverted); // returns a tuple including the bool that keeps track of the sign 
        }                                                     // the tuple currently prevents the function from happening at compile time. Struct also prevents it.
        [[nodiscard]] constexpr matrix get_transpose() const {
            matrix<T, rows, cols> transposedMatrix = {}; // rows and cols are in opposite order for transposed matrix
            
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    transposedMatrix[i][j] = m_data[j][i];
                }
            }
            return transposedMatrix;
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
            matrix<T, cols, rows> resultMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){ // m_data[x] will all have same .size()
                    resultMatrix[i][j] = lhs[i][j] + rhs[i][j];
                }
            }
            return resultMatrix;
        }
        [[nodiscard]] constexpr matrix operator + (const T& scalar)const noexcept {
            matrix<T, cols, rows> resultMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){ 
                    resultMatrix[i][j] = m_data[i][j] + scalar;
                }
            }
            return resultMatrix;
        }
        [[nodiscard]] friend constexpr matrix operator - (const matrix& lhs, const matrix& rhs) noexcept {
            matrix<T, cols, rows> resultMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){ // m_data[x] will all have same .size()
                    resultMatrix[i][j] = lhs[i][j] - rhs[i][j];
                }
            }
            return resultMatrix;
        }
        [[nodiscard]] constexpr matrix operator - (const T& scalar) const noexcept {
            matrix<T, cols, rows> resultMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){ 
                    resultMatrix[i][j] = m_data[i][j] - scalar;
                }
            }
            return resultMatrix;
        }
        template<std::size_t otherRows, std::size_t otherCols>
        [[nodiscard]] constexpr matrix operator * (const matrix<T, otherCols, otherRows>& other) const noexcept { 
            matrix<T, cols, otherRows> resultMatrix = {};
            for(size_t i = 0; i < otherRows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    for(size_t k = 0; k < rows; ++k){
                        resultMatrix[i][j] += m_data[i][k] * other[k][j];
                    }
                }
            }
            return resultMatrix;
        }
        [[nodiscard]] constexpr matrix operator * (const T& scalar) const noexcept {
            matrix<T, cols, rows> resultMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    resultMatrix[i][j] = m_data[i][j] * scalar;
                }
            }
            return resultMatrix;
        }
        template<size_t otherRows, size_t otherCols>
        [[nodiscard]] constexpr matrix operator / (matrix<T, otherCols, otherRows>& other) const noexcept {
            matrix invertedMatrix = other.get_inverse();
            return (*this * invertedMatrix);
        }
        [[nodiscard]] constexpr matrix operator / (const T& scalar) const noexcept {
            matrix<T, cols, rows> resultMatrix = {};
            for(size_t i = 0; i < rows; ++i){
                for(size_t j = 0; j < cols; ++j){
                    resultMatrix[i][j] = m_data[i][j] / scalar;
                }
            }
            return resultMatrix;
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
        template<std::size_t otherRows, std::size_t otherCols>
        constexpr matrix& operator *= (const matrix<T, otherCols, otherRows>& other) noexcept {
            *this = *this * other;
            return *this;
        }
        constexpr matrix& operator *= (const T& scalar) noexcept {
            *this = *this * scalar;
            return *this;
        }
        template<std::size_t otherRows, std::size_t otherCols>
        constexpr matrix& operator /= (const matrix<T, otherCols, otherRows>& other) noexcept {
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
        [[nodiscard]] constexpr reference at(size_t rowIndex, size_t colIndex){
            if(rowIndex >= rows || colIndex >= cols){
                throw std::out_of_range("Element out of range");
            }
            return m_data[rowIndex][colIndex];
        }
        [[nodiscard]] constexpr const_reference at(size_t rowIndex, size_t colIndex) const {
            if(rowIndex >= rows || colIndex >= cols){
                throw std::out_of_range("Element out of range");
            }
            return m_data[rowIndex][colIndex];
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

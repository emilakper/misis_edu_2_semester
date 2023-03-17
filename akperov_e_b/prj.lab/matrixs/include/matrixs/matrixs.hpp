#pragma once
#ifndef MATRIXS_MATRIXS_HPP_20230317
#define MATRIXS_MATRIXS_HPP_20230317

#include <sstream>
#include <vector>

const std::exception out_of_range("Error: Not valid index");

class MatrixS {
public:
    MatrixS() = default;
    MatrixS(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count);
    MatrixS(const MatrixS&) = default;
    ~MatrixS() = default;
    MatrixS& operator=(const MatrixS& rhs) = default;

    std::ptrdiff_t rowCount() const noexcept { return n_row_; }
    std::ptrdiff_t colCount() const noexcept { return n_col_; }
    int32_t& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col);
    int32_t at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const;

    void Resize(const std::ptrdiff_t new_i, const std::ptrdiff_t new_j);
    void resize(const std::ptrdiff_t new_i, const std::ptrdiff_t new_j);
private:
    std::ptrdiff_t n_row_{ 0 };
    std::ptrdiff_t n_col_{ 0 };
    std::vector<int32_t> data_;
};

#endif
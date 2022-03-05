#ifndef WEEK1_MATRIX_H
#define WEEK1_MATRIX_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>


class Matrix{
private:
    std::vector<std::vector<int>> matrix;
    int num_rows_;
    int num_cols_;

public:
    Matrix() : num_cols_(0), num_rows_(0) {}
    Matrix(int num_rows, int num_cols);

    void Reset(int num_rows, int num_cols);

    int At(int num_rows, int num_cols) const;
    int& At(int num_rows, int num_cols);

    int GetNumRows() const;
    int GetNumCols() const;

};

std::istream& operator>>(std::istream& is, Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
bool operator==(const Matrix& lhs, const Matrix& rhs);
Matrix operator+(const Matrix& lhs, const Matrix& rhs);


#endif //WEEK1_MATRIX_H

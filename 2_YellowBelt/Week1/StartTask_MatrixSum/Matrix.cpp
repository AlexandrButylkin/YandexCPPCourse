#include "Matrix.h"

Matrix::Matrix(int num_rows, int num_cols) {
    if(num_rows < 0 || num_cols < 0) throw std::out_of_range("out_of_range");

    num_cols_ = num_cols;
    num_rows_ = num_rows;
    matrix.assign(num_rows, std::vector<int>(num_cols));
}

void Matrix::Reset(int num_rows, int num_cols){
    if(num_rows < 0 || num_cols < 0) {
        throw std::out_of_range("out_of_range");
    }
    matrix.assign(num_rows, std::vector<int>(num_cols));
}

int Matrix::At(int num_rows, int num_cols) const {
    return matrix.at(num_rows).at(num_cols);
}

int& Matrix::At(int num_rows, int num_cols) {
    return matrix.at(num_rows).at(num_cols);
}

int Matrix::GetNumRows() const {
    return num_rows_;
}

int Matrix::GetNumCols() const {
    return num_cols_;
}


std::istream& operator>>(std::istream& is, Matrix& matrix){
    int n = 0, m = 0;
    is >> n >> m;

    matrix.Reset(n, m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            is >> matrix.At(i, j);
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    os << matrix.GetNumRows() << " " << matrix.GetNumCols() << std::endl;

    for(int i = 0, rows = matrix.GetNumRows(); i < rows; ++i){
        bool first = true;
        for(int j = 0, cols = matrix.GetNumCols(); j < cols; ++j){
            if(!first){
                os << " ";
            }
            first = false;
            os << matrix.At(i, j);
        }
        os << std::endl;
    }
    return os;
}

bool operator==(const Matrix& lhs, const Matrix& rhs){

    if(lhs.GetNumCols() != rhs.GetNumCols() || lhs.GetNumRows() != rhs.GetNumRows()){
        return false;
    }

    for(int i = 0, rows = lhs.GetNumRows(); i < rows; ++i){
        for(int j = 0, cols = lhs.GetNumCols(); j < cols; ++j){
            if(lhs.At(i, j) != rhs.At(i, j)){
                return  false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs){

    if(lhs.GetNumCols() != rhs.GetNumCols() || lhs.GetNumRows() != rhs.GetNumRows()){
        throw std::invalid_argument("invalid_argument");
    }

    Matrix result(lhs.GetNumRows(), rhs.GetNumCols());

    for(int i = 0, rows = lhs.GetNumRows(); i < rows; ++i){
        for(int j = 0, cols = lhs.GetNumCols(); j < cols; ++j){
            result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }

    return result;
}
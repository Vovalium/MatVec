#include "Matrix.h"
#include <math.h>
#include "Vector.h"

#include <iostream>

using namespace mat_vec;
using namespace std;

Matrix::Matrix(size_t size, double value) {
    data = new double[size * size];
    rows = size;
    cols = size;
    for (size_t i = 0; i < rows * cols; i++) {
        data[i] = value;
    }
}

Matrix Matrix::eye(size_t size) {
    Matrix result(size);
    for (size_t i = 0; i < size * size; i++) {
        if (i % size == i / size)
            result.data[i] = 1;
    }
    return(result);
}

Matrix::Matrix(size_t rows, size_t cols, double value) {
    data = new double[rows * cols];
    this->rows = rows;
    this->cols = cols;
    for (size_t i = 0; i < rows * cols; i++) {
        data[i] = value;
    }
}

Matrix::Matrix(const Matrix &src) {
    data = new double[src.rows * src.cols];
    rows = src.rows;
    cols = src.cols;
    for (size_t i = 0; i < src.rows * src.cols; i++) {
        data[i] = src.data[i];
    }
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    if (this != &rhs) {
        if ((rhs.rows != rows) || (rhs.cols != cols)) {
            delete[] data;
            rows = 0;
            cols = 0;
            data = nullptr;
            data = new double[rhs.rows * rhs.cols];
            rows = rhs.rows;
            cols = rhs.cols;
        }
        std::copy(rhs.data, rhs.data + rhs.cols * rhs.rows, data);
    }
    return *this;
}

Matrix::~Matrix() {
    delete [] data;
}

void Matrix::reshape(size_t rows, size_t cols) {
    double* dataNew = new double[rows * cols];
    size_t size = rows * cols;

    for (size_t i = 0; i < size; i++) {
        dataNew[i] = data[i];
    }
    delete[] data;
    data = nullptr;
    data = dataNew;

    this-> rows = rows;
    this-> cols = cols;
}

std::pair<size_t, size_t> Matrix::shape() const {
    return std::make_pair(this->rows, this->cols);
}

double Matrix::get(size_t row, size_t col) const {
    return data[row * cols + col];
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    Matrix result = Matrix(rhs.rows, rhs.cols);
    for (size_t i = 0; i < rhs.rows * rhs.cols; i++) {
        result.data[i] = this->data[i] + rhs.data[i];
    }
    return result;
}
Matrix &Matrix::operator+=(const Matrix &rhs) {
    for (size_t i = 0; i < rhs.rows * rhs.cols; i++) {
        this->data[i] += rhs.data[i];
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
    Matrix result = Matrix(rhs.rows, rhs.cols);
    for (size_t i = 0; i < rhs.rows * rhs.cols; i++) {
        result.data[i] = this->data[i] - rhs.data[i];
    }
    return result;
}
Matrix &Matrix::operator-=(const Matrix &rhs) {
    for (size_t i = 0; i < rhs.rows * rhs.cols; i++) {
        this->data[i] -= rhs.data[i];
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
    Matrix result = Matrix(this->rows);
    for (size_t i = 0; i < rhs.rows * this->cols; i++) {
        result.data[i] = 0.0;
        size_t x = i % cols;
        size_t y = i / cols;
        for (size_t j = 0; j < rhs.rows; j++)
            result.data[i] += data[j * cols + x] * rhs.data[y * rhs.cols + j];
    }
    return result;
}

Matrix &Matrix::operator*=(const Matrix &rhs) {
    Matrix result = Matrix(rhs.rows, this->cols, 0);
    for (size_t i = 0; i < rhs.rows * this->cols; i++) {
        result.data[i] = 0.0;
        size_t x = i % cols;
        size_t y = i / cols;
        for (size_t j = 0; j < rhs.rows; j++)
            result.data[i] += data[j * cols + x] * rhs.data[y * rhs.cols + j];
    }
    for(size_t i = 0; i < rows * cols; ++i)
        data[i] = result.data[i];

    this->cols = rhs.rows;

    return *this;
}

Matrix Matrix::operator*(double k) const {
    Matrix result = Matrix(this->rows, this->cols);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        result.data[i] = this->data[i] * k;
    }
    return result;
}

Matrix &Matrix::operator*=(double k) {
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data[i] = this->data[i] * k;
    }
    return *this;
}

Matrix Matrix::operator/(double k) const {
    Matrix result = Matrix(this->rows, this->cols);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        result.data[i] = this->data[i] / k;
    }
    return result;
}

Matrix &Matrix::operator/=(double k) {
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        this->data[i] = this->data[i] / k;
    }
    return *this;
}

Matrix Matrix::transposed() const {
    Matrix result = Matrix(this->cols, this->rows, 0.0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        size_t x = i % cols;
        size_t y = i / cols;
        result.data[x * rows + y] = this->data[y * cols + x];
    }
    result.cols = this->rows;
    result.rows = this->cols;
    return result;
}

void Matrix::transpose() {
    Matrix result = Matrix(this->cols, this->rows, 0.0);
    for (size_t i = 0; i < this->rows * this->cols; i++) {
        size_t x = i % cols;
        size_t y = i / cols;
        result.data[x * rows + y] = this->data[y * cols + x];
    }
    for(size_t i = 0; i < rows * cols; ++i)
        this->data[i] = result.data[i];
    this->rows = result.cols;
    this->cols = result.rows;
}

double Matrix::det() const {
    size_t n = this->rows;
    if (n == 2)
        return ((this->get(0,0) * this->get(1,1)) - (this->get(1,0) * this->get(0,1)));
    double res = 0.0;
    for(size_t cut = 0; cut < rows; ++cut) {
        Matrix mat_temp(rows - 1);
        for(size_t x = 0; x < rows; x++) {
            if (x != cut) {
                for (size_t y = 0; y < cols; y++) {
                    if (y != 0) {
                        size_t xx = x;
                        if (x > cut)
                            xx -= 1;
                        size_t yy = y;
                        if (y > 0)
                            yy -= 1;
                        mat_temp.data[xx + yy * (rows-1)] = this->data[x + y * rows];
                    }
                }
            }
        }

        res += pow(-1, cut) * this->data[cut] * mat_temp.det();
    }
    return res;
}

Matrix Matrix::adj() const {
    Matrix res(rows, cols, 0);
    for(size_t cut = 0; cut < rows * cols; ++cut) {
        Matrix mat_temp(rows - 1);
        for(size_t x = 0; x < rows; x++) {
            if (x != cut % cols) {
                for (size_t y = 0; y < cols; y++) {
                    if (y != cut / cols) {
                        size_t xx = x;
                        if (x > cut % cols)
                            xx -= 1;
                        size_t yy = y;
                        if (y > cut / cols)
                            yy -= 1;
                        mat_temp.data[xx + yy * (rows-1)] = this->data[x + y * rows];
                    }
                }
            }
        }

        res[cut] = pow(-1, cut) * mat_temp.det();
    }
    res.transpose();
    return res;
}

Matrix Matrix::inv() const {
    double val = this->det();
    Matrix temp = this->adj();
    return temp / val;
}

Vector Matrix::operator*(const Vector &vec) const {
    Vector result(vec.size());
    for(size_t i = 0; i< rows; ++i) {
        double temp = 0.0;
        for(size_t j = 0; j< cols; ++j) {
            temp += vec[j] * this->get(i, j);
        }
        result[i] = temp;
    }
    return result;
}

bool Matrix::operator==(const Matrix &rhs) const {
    if ((cols != rhs.cols) || (rows != rhs.rows))
        return false;
    for (size_t i = 0; i < cols * rows; i++) {
        if (data[i] != rhs.data[i])
            return false;
    }
    return true;
}
bool Matrix::operator!=(const Matrix &rhs) const {
    if ((cols != rhs.cols) || (rows != rhs.rows))
        return true;
    for (size_t i = 0; i < cols * rows; i++) {
        if (data[i] != rhs.data[i])
            return true;
    }
    return false;
}

double Matrix::operator[](size_t n) const {
    return data[n];
}

double &Matrix::operator[](size_t n) {
    return data[n];
}
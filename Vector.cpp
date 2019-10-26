#include "Vector.h"
#include "math.h"
#include "Matrix.h"

using namespace mat_vec;
using namespace std;

Vector mat_vec::operator*(double k, const Vector &v) {
    return v * k;
}

Vector::Vector(size_t size, double value):data(nullptr),len(size) {
    if (size == 0)
        return;
    data = new double[size];
    for (size_t i = 0; i < len; i++) {
        data[i] = value;
    }
}

Vector::Vector(const Vector &src):data(nullptr),len(src.len) {
    if (src.len == 0)
        return;
    data = new double[src.len];
    for (size_t i = 0; i < src.len; i++) {
        data[i] = src.data[i];
    }
}

Vector &Vector::operator=(const Vector &rhs) {
    delete [] data;
    std::copy(rhs.data, rhs.data + rhs.len, data);
    this->len = rhs.len;
    return *this;
}

Vector::~Vector() {
    delete [] data;
}

size_t Vector::size() const {
    return len;
}

double Vector::operator[](size_t n) const {
    return data[n];
}

double &Vector::operator[](size_t n) {
    return data[n];
}

double Vector::norm() const {
    double result = 0.0;
    for (size_t i = 0; i < len; ++i)
        result += data[i] * data[i];
    return sqrt(result);
}

Vector Vector::normalized() const {
    double vec = this->norm();
    Vector result(this->len);
    for (size_t i = 0; i < len; ++i)
        result.data[i] = data[i] / vec;
    return(result);
}

void Vector::normalize() {
    double vec = this->norm();
    for (size_t i = 0; i < len; ++i)
        data[i] /= vec;
}

Vector Vector::operator+(const Vector &rhs) const {
    Vector result = Vector(rhs.len);
    for (size_t i = 0; i < rhs.len; i++) {
        result.data[i] = this->data[i] + rhs.data[i];
    }
    return result;
}
Vector &Vector::operator+=(const Vector &rhs) {
    for (size_t i = 0; i < rhs.len; i++) {
        this->data[i] += rhs.data[i];
    }
    return *this;
}

Vector Vector::operator-(const Vector &rhs) const {
    Vector result = Vector(rhs.len);
    for (size_t i = 0; i < rhs.len; i++) {
        result.data[i] = this->data[i] - rhs.data[i];
    }
    return result;
}

Vector &Vector::operator-=(const Vector &rhs) {
    for (size_t i = 0; i < rhs.len; i++) {
        this->data[i] -= rhs.data[i];
    }
    return *this;
}

Vector Vector::operator^(const Vector &rhs) const {
    Vector result = Vector(rhs.len);
    for (size_t i = 0; i < rhs.len; i++) {
        result.data[i] = this->data[i] * rhs.data[i];
    }
    return result;
}

Vector &Vector::operator^=(const Vector &rhs) {
    for (size_t i = 0; i < rhs.len; i++) {
        this->data[i] *= rhs.data[i];
    }
    return *this;
}

double Vector::operator*(const Vector &rhs) const {
    double result = 0.0;
    for (size_t i = 0; i < rhs.len; i++) {
        result += this->data[i] * rhs.data[i];
    }
    return result;
}

Vector Vector::operator*(double k) const {
    Vector result = Vector(len);
    for (size_t i = 0; i < len; i++) {
        result.data[i] = this->data[i] * k;
    }
    return result;
}

Vector &Vector::operator*=(double k) {
    for (size_t i = 0; i < len; i++) {
        this->data[i] *= k;
    }
    return *this;
}

Vector Vector::operator/(double k) const {
    Vector result = Vector(len);
    for (size_t i = 0; i < len; i++) {
        result.data[i] = this->data[i] / k;
    }
    return result;
}

Vector &Vector::operator/=(double k) {
    for (size_t i = 0; i < len; i++) {
        this->data[i] /= k;
    }
    return *this;
}

Vector Vector::operator*(const Matrix &mat) const {
    size_t rows = mat.shape().first;
    size_t cols = mat.shape().second;
    Vector result(cols);
    for(size_t i = 0; i< rows; ++i) {
        double temp = 0.0;
        for(size_t j = 0; j < cols; ++j) {
            temp += data[j] * mat.get(i, j);
        }
        result[i] = temp;
    }
    return result;
}

Vector &Vector::operator*=(const Matrix &mat) {
    size_t rows = mat.shape().first;
    size_t cols = mat.shape().second;
    Vector result(cols);
    for(size_t i = 0; i< rows; ++i) {
        double temp = 0.0;
        for(size_t j = 0; j < cols; ++j) {
            temp += data[j] * mat.get(i, j);
        }
        result[i] = temp;
    }

    delete[] data;
    data = new double[cols];

    for(size_t i = 0; i< rows; ++i) {
        this->data[i] = result.data[i];
    }
    return *this;
}

bool Vector::operator==(const Vector &rhs) const {
    if (len != rhs.len)
        return false;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i])
            return false;
    }
    return true;
}

bool Vector::operator!=(const Vector &rhs) const {
    if (len != rhs.len)
        return true;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i])
            return true;
    }
    return false;
}
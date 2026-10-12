#pragma once

#include <vector>
#include <ostream>
#include <istream>

#ifdef OMP_VERSION
#include <omp.h>
#endif



class Matrix {
private:
    std::vector<std::vector<double>> matrix;

public:
    using vector_1d = std::vector<double>;
    using vector_2d = std::vector<vector_1d>;

    Matrix();
    Matrix(size_t n, size_t m);
    Matrix(size_t n, size_t m, double dft);
    Matrix(const std::vector<std::vector<double>> &matrix);

    size_t csize();
    size_t rsize();

    vector_2d get_matrix();

    Matrix gauss_method(const Matrix& b);

    Matrix operator +                   (const Matrix &what) const;
    Matrix operator -                   (const Matrix &what) const;
    Matrix operator *                   (const Matrix &what) const;
    std::vector<double>& operator []    (size_t index);

    friend std::ostream& operator<<     (std::ostream& os, const Matrix& obj);
    friend std::istream& operator>>     (std::istream& is, Matrix& obj);
};
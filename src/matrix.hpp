#pragma once

#include <vector>
#include <ostream>
#include <istream>

#ifdef OMP_VERSION
#include <omp.h>
#endif

#ifdef OMP_VERSION
#warning "OK: OMP_VERSION defined in matrix library"
#else
#warning "BUG: OMP_VERSION NOT defined in matrix library!"
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

    Matrix gauss_method                     (const Matrix& b);
    Matrix relaxation_method                (const Matrix& b, const double h, double eps = 1e-5);
    Matrix gauss_method_for_puasson         (const Matrix& b, const int N);
    Matrix relaxation_method_for_puasson    (const Matrix& B, const int N, const double h, double eps = 1e-5);
    Matrix yacobi_method_for_puasson        (const int N, double h, double (*f)(double, double), double eps = 1e-5);

    Matrix operator +                       (const Matrix &what) const;
    Matrix operator -                       (const Matrix &what) const;
    Matrix operator *                       (const Matrix &what) const;
    
    std::vector<double>& operator []        (int index);
    const std::vector<double>& operator []  (int index) const;
    std::vector<double>& operator []        (size_t index);
    const std::vector<double>& operator []  (size_t index) const;
    

    friend std::ostream& operator<<         (std::ostream& os, const Matrix& obj);
    friend std::istream& operator>>         (std::istream& is, Matrix& obj);
};
#pragma once

#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> matrix;

public:
    Matrix();
    Matrix(const std::vector<std::vector<double>> &matrix);

    Matrix operator + (const Matrix &what);
    Matrix operator - (const Matrix &what);
    Matrix operator * (const Matrix &what);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);
    friend std::istream& operator>>(std::istream& is, Matrix& obj);
};
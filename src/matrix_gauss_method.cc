#include <matrix.hpp>
#include <iostream>

Matrix Matrix::gauss_method(const Matrix& b) {
    if (this->matrix.size() != b.matrix.size()) throw "Count of columns in this matrix and matrix b must be equal!";
    if (b.matrix[0].size() > 1) throw "B matrix should has 1d!";

    Matrix new_matrix(this->matrix), new_b(b.matrix), ans(b.matrix.size(), 1);

    for (int i = 0; i < this->matrix.size(); i++) {
        #ifdef OMP_VERSION
        #pragma omp parallel for num_threads(NUM_THREADS)
        #endif
        for (int j = i + 1; j < this->matrix.size(); j++) {
            double coef = new_matrix[j][i] / new_matrix[i][i];
            for (int k = 0; k < this->matrix[0].size(); k++) {
                new_matrix[j][k] -= coef * new_matrix[i][k];
            }
            new_b[j][0] -= coef * new_b[i][0];
        }
    }

    for (int i = this->matrix.size() - 1; i > -1; --i) {
        double s = new_b[i][0];
        #ifdef OMP_VERSION
        #pragma omp parallel for reduction(+:s) num_threads(NUM_THREADS)
        #endif
        for (int j = this->matrix[0].size() - 1; j > i; --j) {
            s -= new_matrix[i][j] * ans[j][0];
        }
        ans[i][0] = s / new_matrix[i][i];
    }

    return ans;
}
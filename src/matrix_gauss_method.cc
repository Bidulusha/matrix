#include <matrix.hpp>
#include <iomanip>
#include <iostream>
#include <chrono>

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


Matrix Matrix::gauss_method_for_puasson(const Matrix& b, const int N) {
    if (this->matrix.size() != b.matrix.size()) throw "Count of columns in this matrix and matrix b must be equal!";
    if (b.matrix[0].size() > 1) throw "B matrix should has 1d!";

    
    Matrix new_matrix(this->matrix), new_b(b.matrix), ans(b.matrix.size(), 1);
    
    for (int i = 0; i < this->matrix.size(); i++) {
        int j_end = i + N > this->matrix.size()? this->matrix.size() : i + N; 
        #ifdef OMP_VERSION
        #pragma omp parallel for num_threads(NUM_THREADS)
        #endif
        for(int j = i + 1; j < j_end; j++) {
            double coef = new_matrix[j][i] / new_matrix[i][i];

            int k_end = std::min((int)this->matrix[0].size(), i + N - 1);
            for (int k = i; k < k_end; ++k) {
                new_matrix[j][k] -= coef * new_matrix[i][k];
            }
            new_b[j][0] -= coef * new_b[i][0];
        }
    }

    for (int i = this->matrix.size() - 1; i > -1; --i) {
        double s = new_b[i][0];

        int j_start = std::min((int)this->matrix[0].size() - 1, i + N - 1);

        #ifdef OMP_VERSION
        #pragma omp parallel for reduction(+:s) num_threads(NUM_THREADS)
        #endif
        for (int j = i + 1; j <= j_start; ++j) {
            s -= new_matrix[i][j] * ans[j][0];
        }
        ans[i][0] = s / new_matrix[i][i];
    }

    return ans;
}
#include <matrix.hpp>
#include <iostream>
#include <limits>
#include <cmath>

Matrix Matrix::relaxation_method(const Matrix& b, const double h, const double eps) {
    double w = 2 / (1 + 2 * sin(M_PI * h / 2));
    double dif = std::numeric_limits<double>::max();

    Matrix x(1, this->matrix.size());

    #ifdef OMP_VERSION
    #pragma omp parallel 
    #endif
    {
        while (dif > eps) {
            dif = 0.0;
            for (int i = 0; i < this->matrix.size(); i++) {
                double last_x = x[0][i];
                x[0][i] = (1 - w) * last_x + w * b[i][0] / this->matrix[i][i];

                #ifdef OMP_VERSION
                #pragma omp parallel for num_threads(NUM_THREADS)
                #endif
                for (int j = 0; j < i; j++) {
                    x[0][i] -= w * x[0][j] * this->matrix[i][j] / this->matrix[i][i];
                }

                #ifdef OMP_VERSION
                #pragma omp parallel for num_threads(NUM_THREADS)
                #endif
                for (int j = i+1; j < this->matrix[0].size(); j++) {
                    x[0][i] -= w * x[0][j] * this->matrix[i][j] / this->matrix[i][i];
                }

                dif = std::max(dif, abs(x[0][i] - last_x));
            }
        }
    }

    return x;
}


Matrix Matrix::relaxation_method_for_puasson(const Matrix& b, const int N, const double h, const double eps) {
    double w = 2 / (1 + 2 * sin(M_PI * h / 2));
    double dif = std::numeric_limits<double>::max();

    Matrix x(1, this->matrix.size());

    // #ifdef OMP_VERSION
    // #pragma omp parallel 
    // #endif
    {
        while (dif > eps) {
            dif = 0.0;
            for (int i = 0; i < this->matrix.size(); i++) {
                double last_x = x[0][i], temp = 0;

                int j_start = std::max(0, i - N);
                int j_end = std::min((int)this->matrix[0].size(), i + N);

                x[0][i] = (1 - w) * last_x + w * b[i][0] / this->matrix[i][i];

                // #ifdef OMP_VERSION
                // #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:temp)
                // #endif
                for (int j = j_start; j < i; j++) {
                    temp -= w * x[0][j] * this->matrix[i][j] / this->matrix[i][i];
                }

                // #ifdef OMP_VERSION
                // #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:temp)
                // #endif
                for (int j = i+1; j < j_end; j++) {
                    temp -= w * x[0][j] * this->matrix[i][j] / this->matrix[i][i];
                }

                x[0][i] += temp;

                dif = std::max(dif, abs(x[0][i] - last_x));
            }
        }
    }
    return x;
}
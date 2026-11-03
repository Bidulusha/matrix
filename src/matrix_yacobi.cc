#include    <cmath>
#include    <vector>
#include    <matrix.hpp>
#include    <iostream>
#include    <limits.h>


Matrix Matrix::yacobi_method_for_puasson(const int N, double h, double (*f)(double, double), double eps) {
    Matrix last(this->matrix); 
    Matrix copy(last);
    double dif = std::numeric_limits<double>::max();
    int count = 0;
    int m = N - 2;
    while(dif > eps) {
        dif = 0.0;
        #ifdef OMP_VERSION
        #pragma omp parallel for num_threads(NUM_THREADS) reduction(max:dif)
        #endif
        for (int i = 1; i < this->matrix.size()-1; i++) {
            for (int j = 1; j < this->matrix[0].size()-1; j++){
                copy[i][j] = (last[i][j-1] + last[i][j+1] + last[i-1][j] + last[i+1][j] - h*h * f(h*j, h*i)) / 4;
                dif = std::max(dif, abs(copy[i][j] - last[i][j]));
            }
        }
        std::swap(last, copy);
        count++;
    }    

    std::cout << count << std::endl;

    return last;
}
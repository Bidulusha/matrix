#include <matrix.hpp>

/*_________________ CONSTRUCTORS _________________*/
Matrix::Matrix() {
    this->matrix = std::vector<std::vector<double>> {};
}

Matrix::Matrix(size_t n, size_t m) {
    this->matrix = std::vector<std::vector<double>> (n, std::vector<double>(m)); 
}

Matrix::Matrix(size_t n, size_t m, double dft) {
    this->matrix = std::vector<std::vector<double>> (n, std::vector<double>(m, dft)); 
}

Matrix::Matrix(const std::vector<std::vector<double>> &matrix) {
    this->matrix = std::vector<std::vector<double>>(matrix.size());
    #ifdef OMP_VERSION
    #pragma omp parallel for num_threads(NUM_THREADS)
    #endif
    for (int i = 0; i < matrix.size(); i++) {
        this->matrix[i] = std::vector<double>(matrix[i].size());
        std::copy(matrix[i].begin(), matrix[i].end(), this->matrix[i].begin());
    }
    this->matrix = matrix;
}
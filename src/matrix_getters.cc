#include <matrix.hpp>

size_t Matrix::csize() { return matrix.size(); }
size_t Matrix::rsize() { 
    if (matrix.size() != 0) return matrix[0].size(); 
    return -1;
}

std::vector<std::vector<double>> Matrix::get_matrix() {return this->matrix;}
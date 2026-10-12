#include <matrix.hpp>


/*_________________ OPERATORS _________________*/
Matrix Matrix::operator +(const Matrix &what) const{
    if (what.matrix.size() == 0 || this->matrix.size() == 0) return this->matrix;

    if (what.matrix.size() != this->matrix.size() || what.matrix[0].size() != this->matrix[0].size()) {
        return this->matrix;
    }

    std::vector<std::vector<double>> new_matrix(what.matrix.size());

    #ifdef OMP_VERSION
    #pragma omp parallel for num_threads(NUM_THREADS)
    #endif
    for(int i = 0; i < what.matrix.size(); i++) {
        new_matrix[i] = std::vector<double>(what.matrix[i].size());
        for(int j = 0; j < what.matrix.size(); j++) {
            new_matrix[i][j] = what.matrix[i][j] + this->matrix[i][j];
        }
    }

    return Matrix(new_matrix);
} 

Matrix Matrix::operator -(const Matrix &what) const{
    if (what.matrix.size() == 0 || this->matrix.size() == 0) throw "Null matrix";

    if (what.matrix.size() != this->matrix.size() || what.matrix[0].size() != this->matrix[0].size()) {
        throw "Size not equals";
    }

    std::vector<std::vector<double>> new_matrix(what.matrix.size());

    #ifdef OMP_VERSION
    #pragma omp parallel for num_threads(NUM_THREADS)
    #endif
    for(int i = 0; i < what.matrix.size(); i++) {
        new_matrix[i] = std::vector<double>(what.matrix[i].size());
        for(int j = 0; j < what.matrix.size(); j++) {
            new_matrix[i][j] = what.matrix[i][j] - this->matrix[i][j];
        }
    }

    return Matrix(new_matrix);
} 

Matrix Matrix::operator *(const Matrix &what) const{
    if (this->matrix.size() == 0 || what.matrix.size() == 0) throw "Null matrix";
    if (this->matrix[0].size() != what.matrix.size()) throw "N not equal to M";

    std::vector<std::vector<double>> new_matrix(what.matrix.size());

    #ifdef OMP_VERSION
    #pragma omp parallel for num_threads(NUM_THREADS)
    #endif
    for (int i = 0; i < this->matrix.size(); i++) {
        new_matrix[i] = std::vector<double>(what.matrix[i].size());
        for(int j = 0; j < this->matrix[0].size(); j++) {
            for (int k = 0; k < this->matrix[i].size(); k++) {
                new_matrix[i][j] += this->matrix[i][k] * what.matrix[k][j];
            }
        }
    }

    return Matrix(new_matrix);
}

std::vector<double>& Matrix::operator [](size_t index) {
    return this->matrix[index];
}

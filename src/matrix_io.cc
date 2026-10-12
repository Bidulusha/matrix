#include <iostream>
#include <iomanip>

#include <matrix.hpp>

/*_________________ OS IS _________________*/
std::ostream& operator<<(std::ostream&os, const Matrix& obj){
    for(auto& row: obj.matrix) {
        for (auto& ele: row) {
            os << std::setw(12) << ele << "|";
        }
        os << std::endl;
    }

    return os;
}
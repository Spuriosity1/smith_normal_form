#ifndef PRINT_MATRIX_H
#define PRINT_MATRIX_H

#include <vector>
#include "matrix.hpp"
#include <ostream>

int DigitLength(int a);

int EntryFatness(const Matrix<int>& M);



template <typename Ring>
std::ostream &operator<< (std::ostream &os, const Matrix<Ring> &M){
    int fatness = EntryFatness(M);
    for (int rowIndex = 0; rowIndex < M.GetHeight(); rowIndex++ ) {
        const std::vector<int>& row = M[rowIndex];
        for (int x: row) {
            if (x>=0) {
                os << " "; // extra space for lack of minus sign.
            }
            os << " " << x;
            for (int i=0; i < fatness - DigitLength(x); i++) {
                os << " ";
            }
        }
        os << "\n";
    }
    os << "\n \n";
    return os;
}



#endif

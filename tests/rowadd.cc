#include "matrixOperations.hpp"
#include "printmatrix.hpp"
#include <fstream>
#include <matrix.hpp>
#include <smithNormalForm.hpp>
#include <iostream>
#include <sstream>
#include <string>

///////////////////////////////////////////////////////////////
/// Checks whether decompositions work for some test cases ////

typedef std::vector<std::vector<int>> _mat_t;

using namespace SmithNormalFormCalculator;
int main (int argc, char *argv[]) {

    Matrix<int> A(_mat_t({
                {4, 2, 1, 0},
                {1,0,-9,1},
                {7,3,-1,0}
                }));
    Matrix<int> A_original(A);
    Matrix<int> ops(A.GetHeight());
    std::cout << A;
    rowAdd(A, -7, 1, 2, ops);
    std::cout << A;
    rowAdd(A, -4, 1, 0, ops);
    std::cout << A;
    rowSwap(A, 0, 1, ops);
    std::cout << A;
    return 0;
}

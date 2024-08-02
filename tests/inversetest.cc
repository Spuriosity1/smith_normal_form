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

using namespace SmithNormalFormCalculator;
int main (int argc, char *argv[]) {
    if (argc < 2){
        std::cerr<<"USAGE: inversetest matrix_to_decompose"<<std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs.good()){
        std::cerr<<"Could not open file " << argv[1] <<std::endl;
    }

    std::vector<std::vector<int>> tmp;
    for (std::string line; std::getline(ifs, line);){
        if (line.length() ==0 || line[0] == '#') continue;

        tmp.push_back({});
        std::istringstream iss(line);
        for (std::string t; std::getline(iss, t, ' ');){
            tmp.back().push_back(stoi(t));
        }
    } 
    Matrix<int> A(tmp);
    auto A_inv = inverse(A);

    int status = 0;


    std::cout<<"A = " << A << "\n";
    std::cout<<"A^-1 = " << A_inv << "\n";
    std::cout<<"A^-1 * A = " << A_inv * A <<"\n";
    
    std::cout<<"A * A^-1 = " << A * A_inv <<"\n";

    if (A_inv * A != IdentityMatrix<int>(A.GetWidth())){
        status |= 1;
    }
    if (A * A_inv != IdentityMatrix<int>(A.GetWidth())){
        status |= 2;
    }
    
    return status;
}

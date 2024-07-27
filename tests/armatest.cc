#include "printmatrix.hpp"
#include <fstream>
#include <matrix.hpp>
#include <smithNormalForm.hpp>
#include <iostream>
#include <sstream>
#include <string>

///////////////////////////////////////////////////////////////
/// Checks whether armadillo constructors work  ////
using namespace SmithNormalFormCalculator;
int main (int argc, char *argv[]) {
    if (argc < 2){
        std::cerr<<"USAGE: armatest matrixfile"<<std::endl;
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
    std::cout << "Loaded mat\n" << A;
    auto A_arma_copy = A.to_armadillo();
    Matrix<int> A2(A_arma_copy);
    auto A_arma_copy_2 = A2.to_armadillo();


    int retval = 0;
    if (arma::norm(A_arma_copy - A_arma_copy_2, "inf") != 0){
        std::cout << "Arma matrices differ:\n" << A_arma_copy; 
        std::cout << "=/=\n" << A_arma_copy_2 << std::endl; 
        retval |= 0x01;
    }


    if (A != A2){
        std::cout << "Full matrices differ:\n" << A_arma_copy; 
        std::cout << "=/=\n" << A_arma_copy_2 << std::endl; 
        retval |= 0x02;
    }

    return retval;
    
}



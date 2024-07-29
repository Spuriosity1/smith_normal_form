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
        std::cerr<<"USAGE: snftest matrix_to_decompose"<<std::endl;
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
    SmithNormalFormDecomposition result = ComputeSmithNormalForm(A);
	auto res1 = result.L * A * result.R;
    std::cout << "Decomposed A= " << A << "as follows:\n"; 
    std::cout << "L = " << result.L <<"\n";
    std::cout << "D = " << result.D <<"\n";
    std::cout << "R = " << result.R <<"\n";
    std::cout << result.L << " * " << A << " * " << result.R << " = " << result.D;

    int retval = 0;
    // check that the decomposition is correct
    if (res1 != result.D){
        retval |= 0x01;
    }
    // check that D is truly diagonal
    for (unsigned i=0; i<A.GetHeight(); i++){
        for (unsigned j=0; j<A.GetWidth(); j++){
            if (i != j && result.D[i][j] !=0) {
               retval |= 0x02; 
            }
        }
    }
    return retval;
}

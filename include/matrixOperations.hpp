#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.hpp"

namespace SmithNormalFormCalculator{
	typedef unsigned long idx_t;
//TODO: these should be operators in a vector/matrix class
std::vector<int> add(const std::vector<int>& v, const std::vector<int>& w);
std::vector<int> scale(int a, const std::vector<int>& v);

Matrix<int> IdentityMatrix(idx_t d);

void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j, 
	Matrix<int>& L);

void rowMult (Matrix<int>& M, int a, idx_t i, 
	Matrix<int>& L);

void columnAdd (Matrix<int>& M, int a, idx_t i, idx_t j, 
	Matrix<int>& R);

void rowSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int>& L);

void columnSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int>& R);
};

#endif

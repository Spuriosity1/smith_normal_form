#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.hpp"

namespace SmithNormalFormCalculator{
	typedef unsigned long idx_t;

Matrix<int> IdentityMatrix(idx_t d);

// Applies the operation row(j) -> a*row(i) + row(j) to M 
// Optionally, also applies it to L
// Applies the inverse operation to Linv
void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j);
void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
		Matrix<int> &L);
void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
		Matrix<int> &L, Matrix<int>&L_inv);


// Applies the operation col(j) -> a*col(i) + col(j) to M 
// Optionally, also applies it to R
// Applies the inverse operation to Rinv
void colAdd (Matrix<int>& M, int a, idx_t i, idx_t j);
void colAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
		Matrix<int> &R);
void colAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
		Matrix<int> &R, Matrix<int>&R_inv);


// Applies the operation row(j) <-> row(i) to M 
// Optionally, also applies it to L
// Applies the inverse operation to Linv
void rowSwap (Matrix<int>& M, idx_t i, idx_t j);
void rowSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int> &L);
void rowSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int> &L, Matrix<int> &L_inv);


// Applies the operation col(j) <-> col(i) to M 
// Optionally, also applies it to R
// Applies the inverse operation to Rinv
void colSwap (Matrix<int>& M, idx_t i, idx_t j);
void colSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int> &R);
void colSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int> &R, Matrix<int> &R_inv);




};

#endif

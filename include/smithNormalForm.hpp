#ifndef SNF_H
#define SNF_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <string>

#include "matrix.hpp"


namespace SmithNormalFormCalculator {

struct SmithNormalFormDecomposition {
	SmithNormalFormDecomposition(Matrix<int> left, Matrix<int> diag, Matrix<int> right) :
		L(left),
		D(diag),
		R(right) {}

    Matrix<int> L;
    Matrix<int> D;
    Matrix<int> R;
    };

int remainder(int a, int b);

int quotient(int a, int b);

void killRowEntry (Matrix<int>& M, int columnIndex, int killerRowIndex, 
	int victimRowIndex, Matrix<int>& A);

void killLowerPart (Matrix<int>& M, int columnIndex, int rowIndex, 
	Matrix<int>& L);

void killColumnEntry (Matrix<int>& M, int rowIndex, int killerColumnIndex, 
	int victimColumnIndex, Matrix<int>& A);

void killRightPart (Matrix<int>& M, int rowIndex, int columnIndex, 
	Matrix<int>& A);

void CreateGCDinTopLeft (Matrix<int>& M, int leftColumnIndex, int rightColumnIndex,
	int stage, Matrix<int>& L, Matrix<int>& R);

SmithNormalFormDecomposition ComputeSmithNormalForm (Matrix<int> M);

}; // end of namespace

#endif

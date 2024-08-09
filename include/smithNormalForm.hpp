#ifndef SNF_H
#define SNF_H

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <math.h>
#include <string.h>
#include <string>
#include <cassert>

#include "matrix.hpp"
#include "matrix.hpp"
#include "printmatrix.hpp"
#include "matrixOperations.hpp"

namespace SmithNormalFormCalculator {

template<typename Ring>
struct SmithNormalFormDecomposition {
	SmithNormalFormDecomposition(Matrix<Ring> left, Matrix<Ring> diag, Matrix<Ring> right) :
		L(left),
		D(diag),
		R(right) {}

    Matrix<Ring> L;
    Matrix<Ring> D;
    Matrix<Ring> R;
    };
/*
template<typename Ring>
Ring remainder(Ring a, Ring b);

template<typename Ring>
Ring quotient(Ring a, Ring b);

template<typename Ring>
void killRowEntry (Matrix<Ring>& M, Ring columnIndex, Ring killerRowIndex, 
	Ring victimRowIndex, Matrix<Ring>& L);

template<typename Ring>
void killLowerPart (Matrix<Ring>& M, int columnIndex, int rowIndex, 
	Matrix<Ring>& L);

template<typename Ring>
void killColumnEntry (Matrix<Ring>& M, int rowIndex, int killerColumnIndex, 
	int victimColumnIndex, Matrix<Ring>& R);

template<typename Ring>
void killRightPart (Matrix<Ring>& M, int rowIndex, int columnIndex, 
	Matrix<Ring>& A);

template<typename Ring>
void CreateGCDinTopLeft (Matrix<Ring>& M, int leftColumnIndex, int rightColumnIndex,
	int stage, Matrix<Ring>& L, Matrix<Ring>& R);

template<typename Ring>
SmithNormalFormDecomposition<Ring> ComputeSmithNormalForm (const Matrix<Ring>& M);

template<typename Ring>
Matrix<Ring> inverse( const Matrix<Ring>& _M);


*/

template<typename Ring>
Ring remainder(Ring a, Ring b) { // returns 0<= r <b such that r=a mod b
    if ( b<0) {
        b=-b;
    }
    if ( a<0 ) {
        return (a%b)+b;
    }
    return a%b;
}

template<typename Ring>
Ring quotient(Ring a, Ring b) { // returns q where a=q*b+r where 0<=r<b.
    return (a - remainder(a,b))/b;
}

template<typename Ring>
void killRowEntry (Matrix<Ring>& M, idx_t columnIndex, idx_t killerRowIndex, 
    idx_t victimRowIndex, Matrix<Ring>& L) {

    Ring q;
    while ( M[victimRowIndex][columnIndex] != 0  ) {
        q=quotient(M[killerRowIndex][columnIndex], M[victimRowIndex][columnIndex]);
        rowAdd(M, -q, victimRowIndex, killerRowIndex, L);
        rowSwap(M, killerRowIndex, victimRowIndex, L);
    }
}

template<typename Ring>
void killLowerPart (Matrix<Ring>& M, idx_t rowIndex, idx_t columnIndex, 
    Matrix<Ring>& L) {

    for (unsigned long i=rowIndex+1; i<M.GetHeight(); i++) {
        killRowEntry(M, columnIndex, rowIndex, i , L);
    }
}

template<typename Ring>
void killColumnEntry (Matrix<Ring>& M, idx_t rowIndex, idx_t killerColumnIndex, 
    idx_t victimColumnIndex, Matrix<Ring>& R) {

    Ring q;
    while ( M[rowIndex][victimColumnIndex] != 0 ) {
        q=quotient(M[rowIndex][killerColumnIndex] ,M[rowIndex][victimColumnIndex]);
        columnAdd(M, -q, victimColumnIndex, killerColumnIndex, R);
        columnSwap(M, killerColumnIndex, victimColumnIndex, R);
    }
}

template<typename Ring>
void killRightPart (Matrix<Ring>& M, idx_t rowIndex, idx_t columnIndex, 
    Matrix<Ring>& A) {
    for (unsigned long i=columnIndex+1; i<M.GetWidth(); i++) {
        killColumnEntry(M, rowIndex, columnIndex,i , A);}
}

/**
 * Creates the GCD of column [leftColumnIndex] in the upper left of M,
 * then creates the GCD of row [stage] in the entry (stage, leftColumnIndex). (I think??)
 *
 */
template<typename Ring>
void CreateGCDinTopLeft (Matrix<Ring>& M, idx_t leftColumnIndex, idx_t rightColumnIndex, 
    idx_t stage, Matrix<Ring>& L, Matrix<Ring>& R) {

    while (true) {
        killLowerPart(M, stage, leftColumnIndex, L);	
        if (M[stage][rightColumnIndex]==0) {
            break;
		} else {
			killColumnEntry(M, stage, leftColumnIndex, rightColumnIndex, R);
		}
    }
    // A.S. 2024-08-07
    // I commented these lines out, since the decomposition seems successful
    // without them on any test cases I could find. Of course, the plural of
    // "test case" is not "proof", but a quick sketch suggests that this is
    // really fine
	// The lines in question:
	//
    // columnAdd(M, static_cast<Ring>(1), rightColumnIndex, leftColumnIndex, R);
    // killLowerPart(M, stage, leftColumnIndex, L);
}

template<typename Ring, bool ensure_positive_D=true>
void _ComputeSmithNormalForm ( Matrix<Ring>& M, Matrix<Ring>& L, Matrix<Ring>& R){
    assert(L.GetWidth() == M.GetHeight());
	assert(M.GetWidth() == R.GetHeight());

	for (idx_t stage=0; ((stage<M.GetWidth()) && (stage<M.GetHeight())); stage++ ) {
		for (idx_t i=stage+1; i<M.GetWidth(); i++ ) {
			CreateGCDinTopLeft (M, stage, i, stage, L, R);
		}
		if (M[stage][stage]==0) {
			break; 
		}
		for (idx_t i=stage+1; i<M.GetWidth(); i++ ) {
			Ring q=(M[stage][i])/(M[stage][stage]);
			columnAdd(M, -q, stage, i, R);
		}
	}

	if constexpr (ensure_positive_D) {
		for (idx_t i=0; i<M.GetHeight() && i<M.GetWidth(); i++){
			if (M[i][i] < 0) {
				rowMult(M, static_cast<Ring>(-1), i, L);
			}
		}
	}
}

template<typename Ring>
SmithNormalFormDecomposition<Ring> ComputeSmithNormalForm (const Matrix<Ring>& M) {
    idx_t height_M = M.GetHeight();
    idx_t width_M = M.GetWidth();

    Matrix<Ring> L = IdentityMatrix<Ring>(height_M);
    Matrix<Ring> R = IdentityMatrix<Ring>(width_M);

    Matrix<Ring> M2;

    if (width_M >= height_M) {
        M2 = M;
        _ComputeSmithNormalForm(M2, L, R);
        return SmithNormalFormDecomposition(L, M2, R);
    } else {
        M2= M.transpose();
        _ComputeSmithNormalForm(M2, R, L);
        return SmithNormalFormDecomposition(L.transpose(), M2.transpose(), R.transpose());
    }
}


template<typename Ring>
Matrix<Ring> inverse( const Matrix<Ring>& _M){ 
    if(_M.GetHeight() != _M.GetWidth()){
		throw std::invalid_argument("M is not square");
	}
    Matrix<Ring> M(_M);
    auto L = IdentityMatrix<Ring>(M.GetHeight());
    // Strategy: 1. Create GCD of first col in top left using row ops.
    // If this is not possible, then the matrix is not invertible so we 
    // raise an exception.
    int curr_row = 0;
    while (curr_row < (int)M.GetHeight()){
        killLowerPart(M, curr_row, curr_row, L);
        if (M[curr_row][curr_row] == -1){
            rowMult(M, static_cast<Ring>(-1), curr_row, L);
        }
		if (M[curr_row][curr_row] != 1){
			throw std::invalid_argument(
					"GCD of a col is not 1 => M is not invertible");
		}
        ++curr_row;
    }

    // Matrix should now be upper triangular.
    for (curr_row = M.GetHeight()-1; curr_row>=0; curr_row--){
        for (idx_t row=0; row<(idx_t)curr_row; row++){
            rowAdd(M, -M[row][curr_row], (idx_t)curr_row, row, L);
        }
    }
    // M should now be the identity matrix.
	if( M != IdentityMatrix<Ring>(M.GetWidth())){
		throw std::logic_error(
				"Inversion failed for unknown reason -\
				please report this issue on GitHub:\
				https://github.com/Spuriosity1/smith_normal_form/issues");
	}
    
    return L;
}



}

#endif

#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <string>

#include "matrix.hpp"
#include "printmatrix.hpp"
#include "matrixOperations.hpp"
#include "smithNormalForm.hpp"

namespace SmithNormalFormCalculator {

int remainder(int a, int b) { // returns 0<= r <b such that r=a mod b
    if ( b<0) {
        b=-b;
    }
    if ( a<0 ) {
        return (a%b)+b;
    }
    return a%b;
}

int quotient(int a, int b) { // returns q where a=q*b+r where 0<=r<b.
    return (a - remainder(a,b))/b;
}

void killRowEntry (Matrix<int>& M, int columnIndex, int killerRowIndex, 
    int victimRowIndex, Matrix<int>& L) {

    int q;
    while ( M[victimRowIndex][columnIndex] != 0  ) {
        q=quotient(M[killerRowIndex][columnIndex], M[victimRowIndex][columnIndex]);
        rowAdd(M, -q, victimRowIndex, killerRowIndex, L);
        rowSwap(M, killerRowIndex, victimRowIndex, L);
    }
}

void killLowerPart (Matrix<int>& M, int rowIndex, int columnIndex, 
    Matrix<int>& L) {

    for (unsigned long i=rowIndex+1; i<M.GetHeight(); i++) {
        killRowEntry(M, columnIndex, rowIndex, i , L);
    }
}

void killColumnEntry (Matrix<int>& M, int rowIndex, int killerColumnIndex, 
    int victimColumnIndex, Matrix<int>& R) {

    int q;
    while ( M[rowIndex][victimColumnIndex] != 0 ) {
        q=quotient(M[rowIndex][killerColumnIndex] ,M[rowIndex][victimColumnIndex]);
        columnAdd(M, -q, victimColumnIndex, killerColumnIndex, R);
        columnSwap(M, killerColumnIndex, victimColumnIndex, R);
    }
}

void killRightPart (Matrix<int>& M, int rowIndex, int columnIndex, 
    Matrix<int>& A) {
    for (unsigned long i=columnIndex+1; i<M.GetWidth(); i++) {
        killColumnEntry(M, rowIndex, columnIndex,i , A);}
}

void CreateGCDinTopLeft (Matrix<int>& M, int leftColumnIndex, int rightColumnIndex, 
    int stage, Matrix<int>& L, Matrix<int>& R) {

    while (true) {
        killLowerPart(M, stage, leftColumnIndex, L);
        if (M[stage][rightColumnIndex]==0) {
            break;
        } else {
            killColumnEntry(M, stage, leftColumnIndex, rightColumnIndex, R);
            }
    }
    columnAdd(M, 1, rightColumnIndex, leftColumnIndex, R);
    killLowerPart(M, stage, leftColumnIndex, L);
}

void _ComputeSmithNormalForm ( Matrix<int>& M, Matrix<int>& L, Matrix<int>& R ){
    assert(L.GetWidth() == M.GetHeight());
    assert(M.GetWidth() == R.GetHeight());

    for (idx_t stage=0; ((stage<M.GetWidth()) && (stage<M.GetHeight())); stage++ ) {
            for (idx_t i=stage+1; i<M.GetWidth(); i++ ) {
                CreateGCDinTopLeft (M, stage, i, stage, L, R);}

        if (M[stage][stage]==0) {
            break; 
        }
        for (idx_t i=stage+1; i<M.GetWidth(); i++ ) {
            int q=(M[stage][i])/(M[stage][stage]);
            columnAdd(M, -q, stage, i, R);}
    }
}


SmithNormalFormDecomposition ComputeSmithNormalForm (const Matrix<int>& M) {
    int height_M = M.GetHeight();
    int width_M = M.GetWidth();

    Matrix<int> L = IdentityMatrix(height_M);
    Matrix<int> R = IdentityMatrix(width_M);

    Matrix<int> M2;

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


Matrix<int> inverse( const Matrix<int>& _M){ 
    assert(_M.GetHeight() == _M.GetWidth());
    Matrix<int> M(_M);
    auto L = IdentityMatrix(M.GetHeight());
    // Strategy: 1. Create GCD of first col in top left using row ops.
    // If this is not possible, then the matrix is not invertible so we 
    // raise an exception.
    int curr_row = 0;
    while (curr_row < (int)M.GetHeight()){
        killLowerPart(M, curr_row, curr_row, L);
        if (M[curr_row][curr_row] == -1){
            rowMult(M, -1, curr_row, L);
        }
        assert(M[curr_row][curr_row] == 1); // assert M invertible
        ++curr_row;
    }

    std::cout << "post-tri: " << M;
    // Matrix should now be upper triangular.
    for (curr_row = M.GetHeight()-1; curr_row>=0; curr_row--){
        for (int row=0; row<curr_row; row++){
            rowAdd(M, -M[row][curr_row], curr_row, row, L);
            std::cout << "row "<<row <<" curr_row "<<curr_row << M;
        }
    }
    // M should now be the identity matrix.
    assert( M == IdentityMatrix(M.GetWidth()));
    
    return L;
}


}; // Namespace end

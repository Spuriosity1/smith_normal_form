#include "matrixOperations.hpp"

namespace SmithNormalFormCalculator {


Matrix<int> IdentityMatrix(idx_t d) {
   Matrix<int> I;
    for (idx_t i=0; i<d; i++) {
        I.push_back({});
        for (idx_t j=0; j<d; j++) {
                I[i].push_back(i==j);
        }
    }
    return I;
}


void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j){
    for (idx_t col=0; col<M.GetWidth(); col++){
        M[j][col] += a*M[i][col];
    }
}

void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j, 
    Matrix<int> &L) {
    for (idx_t col=0; col<M.GetWidth(); col++){
        M[j][col] += a*M[i][col];
        L[j][col] += a*L[i][col];
    }
}
/*
void rowAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
		Matrix<int> &L, Matrix<int>&L_inv){
    for (idx_t col=0; col<M.GetWidth(); col++){
        M[j][col] += a*M[i][col];
        L[j][col] += a*L[i][col];
        L_inv[i][col] -= a*L[j][col];
    }
}
*/

void colAdd (Matrix<int>& M, int a, idx_t i, idx_t j) {
    for (idx_t k=0; k<M.GetHeight(); k++) {
        M[k][j]+=a*(M[k][i]);
    }
}

void colAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
        Matrix<int> &R){
    for (idx_t k=0; k<M.GetHeight(); k++) { 
        M[k][j]+=a*(M[k][i]);
        R[k][j]+=a*(R[k][i]);
    }
}

/*
void colAdd (Matrix<int>& M, int a, idx_t i, idx_t j,
        Matrix<int> &R, Matrix<int> &R_inv){
    for (idx_t k=0; k<M.GetHeight(); k++) { 
        M[k][j]+=a*(M[k][i]);
        R[k][j]+=a*(R[k][i]);
        R_inv[i][k]-=a*(R[j][k]);
    }
}
*/


void rowSwap (Matrix<int>& M, idx_t i, idx_t j) {
    std::swap(M[i], M[j]);
}

void rowSwap (Matrix<int>& M, idx_t i, idx_t j, Matrix<int> &L) {
    std::swap(M[i], M[j]);
    std::swap(L[i], L[j]);
}


/*
void rowSwap (Matrix<int>& M, idx_t i, idx_t j, Matrix<int> &L,
        Matrix<int>& L_inv) {
    std::swap(M[i], M[j]);
    std::swap(L[i], L[j]);
    // L[i][m] <-> L[j][m]
    for (idx_t k=0; k<M.GetHeight(); k++) {
        std::swap(L_inv[k][i], L_inv[k][j]);
    }
}
*/

void colSwap (Matrix<int>& M, idx_t i, idx_t j) {
    for (idx_t k=0; k<M.GetHeight(); k++) {
        std::swap (M[k][j], M[k][i]);
    }
}

void colSwap (Matrix<int>& M, idx_t i, idx_t j, Matrix<int> &R) {
    for (idx_t k=0; k<M.GetHeight(); k++) {
        std::swap (M[k][j], M[k][i]);
        std::swap (R[k][j], R[k][i]);
    }
}

/*
void colSwap (Matrix<int>& M, idx_t i, idx_t j, 
	Matrix<int> &R, Matrix<int> &R_inv){
    for (idx_t k=0; k<M.GetHeight(); k++) {
        std::swap (M[k][j], M[k][i]);
        std::swap (R[k][j], R[k][i]);
        std::swap (R_inv[j][k], R_inv[i][k]);
    }
}
*/


};

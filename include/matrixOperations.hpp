#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.hpp"

namespace SmithNormalFormCalculator{
	typedef unsigned long idx_t;

template <typename Ring>
std::vector<Ring> add(const std::vector<Ring>& v, const std::vector<Ring>& w) {
    std::vector<Ring> sum;
    sum.reserve(v.size());
    std::cout << std::endl;
    for(idx_t i=0; i<v.size(); i++) {
            sum.push_back(v[i]+w[i]);}
    return sum;
}

template<typename Ring>
std::vector<Ring> scale(Ring a, const std::vector<Ring>& v) {
    std::vector<Ring> scaled;
    scaled.reserve(v.size());
    for(idx_t i=0; i<v.size(); i++) {
            scaled.push_back(a * v[i]);}
    return scaled;
}

template<typename Ring>
Matrix<Ring> IdentityMatrix(idx_t d) {
   Matrix<Ring> I;
    for (idx_t i=0; i<d; i++) {
        I.push_back({});
        for (idx_t j=0; j<d; j++) {
                I[i].push_back(i==j);
        }
    }
    return I;
}

//add a times row i to row j
template<typename Ring>
void rowAdd (Matrix<Ring>& M,
        Ring a, idx_t i, idx_t j, 
    Matrix<Ring>& L) {

    M[j]=add(scale(a,M[i]),M[j]);
        L[j]=add(scale(a,L[i]),L[j]);
    
}

template<typename Ring>
void columnAdd (Matrix<Ring>& M, Ring a, idx_t i, idx_t j, 
    Matrix<Ring>& R) {
    for (idx_t k=0; k<M.GetHeight(); k++) {
        M[k][j]=a*(M[k][i])+M[k][j];
    }
    for (idx_t k=0; k<R.GetHeight(); k++) {
        R[k][j]=(a*R[k][i])+R[k][j];
    }
    
}

template<typename Ring>
void rowSwap (Matrix<Ring>& M, idx_t i, idx_t j, Matrix<Ring>& L) {
    std::swap(M[i], M[j]);
    std::swap(L[i], L[j]);
}


template<typename Ring>
void columnSwap (Matrix<Ring>& M, idx_t i, idx_t j, Matrix<Ring>& R) {
    for (idx_t k=0; k<M.GetHeight(); k++) {
        std::swap (M[k][j], M[k][i]);}
        for (idx_t k=0; k<R.GetHeight(); k++) {
            std::swap (R[k][j], R[k][i]);}
    
}

template<typename Ring>
void rowMult (Matrix<Ring>& M, Ring a, idx_t i, 
	Matrix<Ring>& L){
    for (idx_t j=0; j<M.GetWidth(); j++){
        M[i][j] *= a;
    }
    for (idx_t j=0; j<L.GetWidth(); j++){
        L[i][j] *= a;
    }
}





};
#endif

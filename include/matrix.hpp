#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

#ifdef ARMADILLO
#include <armadillo>
#endif

// implementing a matrix where the coefficients form a Ring
// https://en.wikipedia.org/wiki/Ring_(mathematics)
namespace SmithNormalFormCalculator {

template <typename Ring>
class Matrix
{
public:
	Matrix() {}

	Matrix(std::vector<std::vector<Ring>> M) {
		matrix_ = M;
	}

	Matrix(unsigned int rowCount) {
		matrix_.reserve(rowCount);
	}

	void push_back(std::vector<Ring> row) {
		matrix_.push_back(row);
	}

	std::vector<Ring>& operator[] (int rowIndex) {
		return matrix_[rowIndex];
	}

	const std::vector<Ring>& operator[] (int rowIndex) const {
		return matrix_[rowIndex];
	}

	unsigned int GetWidth() const {
		return matrix_[0].size();
	}

	unsigned int GetHeight() const {
		return matrix_.size();
	}

	bool operator==(const Matrix<Ring>& other) const {
		if (this->GetHeight() != other.GetHeight()) return false;
		if (this->GetWidth() != other.GetWidth()) return false;
		for (unsigned long i=0; i< this->GetHeight(); i++){
			for (unsigned long j=0; j<this->GetWidth(); j++){
				if ( matrix_[i][j] != other.matrix_[i][j] ) return false;
			}
		}
		return true;
	}

	Matrix<Ring> transpose() const {
		Matrix<Ring> tr(this->colCount());
		for (size_t i=0; i < this->rowCount; i++){
			for (size_t j=0; j< this->colCount(); j++){
				tr[j][i] = matrix_[i][j];
			}
		}
		return tr;	
	}

// Wrappers (dumb, not clever at all)
//
#ifdef ARMADILLO
	Matrix(const arma::Mat<Ring>& X){
		for (size_t i=0; i < X.n_rows; i++){
			std::vector<Ring> row;
			for (size_t j=0; j< X.n_cols; j++){
				row.push_back( X(i, j) );
			}
			matrix_.push_back(row);
		}
	}
	inline arma::Mat<Ring> to_armadillo() {
		arma::Mat<Ring> retval(GetHeight(), GetWidth());
		for (size_t row=0; row < GetHeight(); row++){
			for (size_t col=0; col<GetWidth(); col++){
				retval(row, col) = matrix_[row][col];
			}
		}
		return retval;
	}


#endif // end wrapper ARMADILLO


private:
	std::vector<std::vector<Ring>> matrix_;
};

// matrix arithmetic
template<typename Ring>
Matrix<Ring> operator*(const Matrix<Ring>& A, const Matrix<Ring>& B) {
	// the number of rows of product is the number of rows in the first matrix A, hence
	// reserve this much size
	// TODO: does resize make more sense?
	Matrix<Ring> productMatrix(A.GetHeight());

	//throw if matrix product undefined?
	if (A.GetWidth() != B.GetHeight()) {
		throw;
	}

	for (unsigned long rowIndex = 0; rowIndex < A.GetHeight(); rowIndex++) {
		//TODO: reserve the size of the row for efficiency
		productMatrix.push_back({});
		for (unsigned long columnIndex = 0; columnIndex < B.GetWidth(); columnIndex++) {
			// construct the rowIndex, columnIndex entry of product matrix here
			Ring newEntry = 0;
			for (unsigned long i=0; i < A.GetWidth(); i++) {
				newEntry += A[rowIndex][i] * B[i][columnIndex];
			}

			productMatrix[rowIndex].push_back(newEntry);
		}
	}

	return productMatrix;
}

}; // End of namespace SmithNormalFormCalculator
#endif


#include "MatrixBuilder.h"


 Matrix& MatrixBuilder::Combine(
 		const MatrixBase& first, const MatrixBase& last, MatrixCombinationType rule) {
 	switch (rule) {
 		case LeftRight:
 			if (first.size(1) != last.size(1)) {
 				throw "ERROR:  "
 					  "Matrix& MatrixBuilder::Combine(const MatrixBase&, const MatrixBase&, MatrixCombinationType)\n"
 					  "\tInput Matrices must have the same number of rows for LeftRight Matrix Combination.";
 			} else {
				int nRows = first.size(1);
				int nColsLeft = first.size(2);
				int nColsRight = last.size(2);
				Matrix& outMatrix = *(new Matrix(nRows, nColsLeft + nColsRight));
				for (int i = 0; i < nRows; ++i) {
					for (int j = 0; j < nColsLeft; ++j) {
						outMatrix(i,j) = first(i,j);
					}
					for (int j = 0; j < nColsRight; ++j) {
						outMatrix(i,j+nColsLeft) = last(i,j);
					}
				}
				return outMatrix;
			}
			break;
		case TopDown:
			if (first.size(2) != last.size(2)) {
				throw "ERROR  "
				  "Matrix& MatrixBuilder::Combine(const MatrixBase&, const MatrixBase&, MatrixCombinationType)\n"
				  "\tInput Matrices must have the same number of columns for TopDown Matrix Combination";
			} else {
				int nCols = first.size(2);
				int nRowsTop = first.size(1);
				int nRowsDown = last.size(1);
				Matrix& outMatrix = *(new Matrix(nRowsTop + nRowsDown, nCols));
				for (int i = 0; i < nRowsTop; ++i) {
					for (int j = 0; j < nCols; ++j) {
						outMatrix(i,j) = first(i,j);
					}
				}
				for (int i = 0; i < nRowsDown; ++i) {
					for (int j = 0; j < nCols; ++j) {
						outMatrix(i+nRowsTop,j) = last(i,j);
					}
				}
				return outMatrix;
			}
			break;
		default:
			throw "ERROR:  "
				  "Matrix& MatrixBuilder::Combine(const MatrixBase&, const MatrixBase&, MatrixCombinationType)\n"
				  "\tUnsupported MatrixCombinationType";
 	}

 }

Matrix& MatrixBuilder::Multiply(const MatrixBase& left, const MatrixBase& right) {
	if (left.size(2) != right.size(1)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::Multiply(const MatrixBase&, const MatrixBase&)\n"
			  "\tInput Matrices must have compatible dimensions for Matrix Multiplication.";
	} else {
		Matrix& outMatrix = *(new Matrix(left.size(1), right.size(2)));
		for (int i = 0; i < left.size(1); ++i) {
			for (int j = 0; j < right.size(2); ++j) {
				double addingValue = 0.0;
				for (int k = 0; k < left.size(2); ++k) {
					addingValue += left(i, k) * right(k, j);
				}
				outMatrix(i, j) = addingValue;
			}
		}
		return outMatrix;
	}
}

// // Build a new Matrix by multiplying a matrix with a submatrix
// // @param const Matrix& left - the left Matrix in the multiplication
// // @param const SubMatrix& right - the right SubMatrix in the multiplication
// // @return - a new Matrix from the multiplication of the other two
// // @throws exceptions for mismatched dimensions.
// Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix& left, const SubMatrix& right) {
// 	if (left.size(2) != right.size(1)) {
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix&, const SubMatrix&)\n"
// 			  "\tInput Matrices must have compatible dimensions for Matrix Multiplication.";
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(left.size(1), right.size(2)));
// 		for (int i = 0; i < left.size(1); ++i) {
// 			for (int j = 0; j < right.size(2); ++j) {
// 				double addingValue = 0.0;
// 				for (int k = 0; k < left.size(2); ++k) {
// 					addingValue += left(i, k) * right(k, j);
// 				}
// 				outMatrix(i, j) = addingValue;
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// // Build a new Matrix by multiplying a submatrix with a matrix.
// // @param const Matrix& left - the left SubMatrix in the multiplication
// // @param const Matrix& right - the right Matrix in the multiplication
// // @return - a new Matrix from the multiplication of the other two
// // @throws exceptions for mismatched dimensions.
// Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix& left, const Matrix& right) {
// 	if (left.size(2) != right.size(1)) {
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix&, const Matrix&)\n"
// 			  "\tInput Matrices must have compatible dimensions for Matrix Multiplication.";
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(left.size(1), right.size(2)));
// 		for (int i = 0; i < left.size(1); ++i) {
// 			for (int j = 0; j < right.size(2); ++j) {
// 				double addingValue = 0.0;
// 				for (int k = 0; k < left.size(2); ++k) {
// 					addingValue += left(i, k) * right(k, j);
// 				}
// 				outMatrix(i, j) = addingValue;
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// // Build a new Matrix by multiplying two submatrices together
// // @param const SubMatrix& left - the left SubMatrix in the multiplication
// // @param const SubMatrix& right - the right SubMatrix in the multiplication
// // @return - a new Matrix from the multiplication of the other two
// // @throws exceptions for mismatched dimensions.
// Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix& left, const SubMatrix& right) {
// 	if (left.size(2) != right.size(1)) {
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix&, const SubMatrix&)\n"
// 			  "\tInput Matrices must have compatible dimensions for Matrix Multiplication.";
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(left.size(1), right.size(2)));
// 		for (int i = 0; i < left.size(1); ++i) {
// 			for (int j = 0; j < right.size(2); ++j) {
// 				double addingValue = 0.0;
// 				for (int k = 0; k < left.size(2); ++k) {
// 					addingValue += left(i, k) * right(k, j);
// 				}
// 				outMatrix(i, j) = addingValue;
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix& mat, double scale) {
// 	if (scale == 0) {
// 		return *(new Matrix(mat.size(1), mat.size(2)));
// 	} else if (scale == 1) {
// 		return *(new Matrix(mat));
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(mat));
// 		for (int i = 0; i < mat.size(1); ++i) {
// 			for (int j = 0; j < mat.size(2); ++j) {
// 				outMatrix(i,j) *= scale;
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// Matrix& MatrixBuilder::BuildMatrixFromAddition(const Matrix& left, const Matrix& right) {
// 	if (left.size(1) != right.size(1) || left.size(2) != right.size(2)) {
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::BuildMatrixFromAddition(const Matrix&, const Matrix&)\n"
// 			  "\tInput Matrices must have compatible dimensions for Matrix Addition.";
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(left));
// 		for (int i = 0; i < left.size(1); ++i) {
// 			for (int j = 0; j < left.size(2); ++j) {
// 				outMatrix(i,j) += right(i,j);
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// Matrix& MatrixBuilder::BuildMatrixFromSubtraction(const Matrix& left, const Matrix& right) {
// 	if (left.size(1) != right.size(1) || left.size(2) != right.size(2)) {
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::BuildMatrixFromSubtraction(const Matrix&, const Matrix&)\n"
// 			  "\tInput Matrices must have compatible dimensions for Matrix Subtraction.";
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(left));
// 		for (int i = 0; i < left.size(1); ++i) {
// 			for (int j = 0; j < left.size(2); ++j) {
// 				outMatrix(i,j) -= right(i,j);
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// Matrix& MatrixBuilder::SumReduce(const Matrix& mat, int dim) {
// 	int nRows = mat.size(1);
// 	int nCols = mat.size(2);
// 	if (dim == 1) {
// 		Matrix& outMatrix = *(new Matrix(1, nCols));
// 		for (int j = 0; j < nCols; ++j) {
// 			for (int i = 0; i < nRows; ++i) {
// 				outMatrix(0,j) += mat(i,j);
// 			}
// 		}
// 		return outMatrix;
// 	} else if (dim == 2) {
// 		Matrix& outMatrix = *(new Matrix(nRows, 1));
// 		for (int i = 0; i < nRows; ++i) {
// 			for (int j = 0; j < nCols; ++j) {
// 				outMatrix(i,0) += mat(i,j);
// 			}
// 		}
// 		return outMatrix;
// 	} else {
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::SumReduce(const Matrix&, int)\n"
// 			  "\tWe only support Matrix reduction with the first or second dimension.";
// 	}
// }

// Matrix& MatrixBuilder::ElementMultiply(SubMatrix& left, const Matrix& right) {
// 	if (left.size(1) != right.size(1) || left.size(2) != right.size(2)) {
// 		delete &left;
// 		throw "ERROR:  "
// 			  "Matrix& MatrixBuilder::ElementMultiply(SubMatrix&, const Matrix&)\n"
// 			  "\tInput Matrices must have compatible dimensions for Matrix element-wise multiplication.";
// 	} else {
// 		Matrix& outMatrix = *(new Matrix(left));
// 		for (int i = 0; i < right.size(1); ++i) {
// 			for (int j = 0; j < right.size(2); ++j) {
// 				outMatrix(i,j) *= right(i,j);
// 			}
// 		}
// 		return outMatrix;
// 	}
// }

// Matrix& MatrixBuilder::Transpose(const Matrix& mat) {
// 	int nRows = mat.size(1);
// 	int nCols = mat.size(2);
// 	Matrix& outMatrix = *(new Matrix(nCols, nRows));
// 	for (int i = 0; i < nRows; ++i) {
// 		for (int j = 0; j < nCols; ++j) {
// 			outMatrix(j,i) = mat(i,j);
// 		}
// 	}
// 	return outMatrix;
// }




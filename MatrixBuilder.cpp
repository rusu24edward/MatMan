
#include "MatrixBuilder.h"

// Build a new Matrix by combining two Matrices according to specification.
// @param const Matrix& first - the first Matrix involved in the combination
// @param const Matrix& last - the second Matrix involved in the combination
// @param MatrixCombinatoinType rule - specify how the Matrices will be combined:
//									   (1) LeftRight
//									   (2) TopDown
// @return - a new Matrix combined from the other two
// @throws exceptions for unsupported MatrixCombinationType and mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromCombination(
		const Matrix& first, const Matrix& last, MatrixCombinationType rule) {
	switch (rule) {
		case LeftRight:
			if (first.size(1) != last.size(1)) {
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tInput Matrices must have the same number of rows for LeftRight Matrix Combination";
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
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, const Matrix&, MatrixCombinationType)\n"
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
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tUnsupported MatrixCombinationType";
	}
}

// Build a new Matrix by combining a Matrix with a SubMatrix according to specification.
// @param const Matrix& first - the Matrix involved in the combination
// @param SubMatrix& last - the SubMatrix involved in the combination
// @param MatrixCombinatoinType rule - specify how the Matrices will be combined:
//									   (1) LeftRight
//									   (2) TopDown
// @return - a new Matrix combined from the other two
// @throws exceptions for unsupported MatrixCombinationType and mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromCombination(
		const Matrix& first, SubMatrix& last, MatrixCombinationType rule) {
	switch (rule) {
		case LeftRight:
			if (first.size(1) != last.size(1)) {
				delete &last;
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, SubMatrix&, MatrixCombinationType)\n"
				  "\tInput Matrices must have the same number of rows for LeftRight Matrix Combination";
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
				delete &last;
				return outMatrix;
			}
			break;
		case TopDown:
			if (first.size(2) != last.size(2)) {
				delete &last;
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, SubMatrix&, MatrixCombinationType)\n"
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
				delete &last;
				return outMatrix;
			}
			break;
		default:
			delete &last;
			throw "ERROR:  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, SubMatrix&, MatrixCombinationType)\n"
				  "\tUnsupported MatrixCombinationType";
	}
}

// Build a new Matrix by combining a SubMatrix with a Matrix according to specification.
// @param SubMatrix& first - the SubMatrix involved in the combination
// @param const Matrix& last - the Matrix involved in the combination
// @param MatrixCombinatoinType rule - specify how the Matrices will be combined:
//									   (1) LeftRight
//									   (2) TopDown
// @return - a new Matrix combined from the other two
// @throws exceptions for unsupported MatrixCombinationType and mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromCombination(
		SubMatrix& first, const Matrix& last, MatrixCombinationType rule) {
	switch (rule) {
		case LeftRight:
			if (first.size(1) != last.size(1)) {
				delete &first;
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(SubMatrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tInput Matrices must have the same number of rows for LeftRight Matrix Combination";
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
				delete &first;
				return outMatrix;
			}
			break;
		case TopDown:
			if (first.size(2) != last.size(2)) {
				delete &first;
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(SubMatrix&, const Matrix&, MatrixCombinationType)\n"
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
				delete &first;
				return outMatrix;
			}
			break;
		default:
			delete &first;
			throw "ERROR:  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(SubMatrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tUnsupported MatrixCombinationType";
	}
}

// Build a new Matrix by combining two SubMatrices according to specification.
// @param SubMatrix& first - the first SubMatrix involved in the combination
// @param SubMatrix& last - the second SubMatrix involved in the combination
// @param MatrixCombinatoinType rule - specify how the Matrices will be combined:
//									   (1) LeftRight
//									   (2) TopDown
// @return - a new Matrix combined from the other two
// @throws exceptions for unsupported MatrixCombinationType and mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromCombination(
		SubMatrix& first, SubMatrix& last, MatrixCombinationType rule) {
	switch (rule) {
		case LeftRight:
			if (first.size(1) != last.size(1)) {
				if (&first == &last) {
					delete &first;
				} else {
					delete &first;
					delete &last;
				}
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(SubMatrix&, SubMatrix&, MatrixCombinationType)\n"
				  "\tInput Matrices must have the same number of rows for LeftRight Matrix Combination";
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
				if (&first == &last) {
					delete &first;
				} else {
					delete &first;
					delete &last;
				}
				return outMatrix;
			}
			break;
		case TopDown:
			if (first.size(2) != last.size(2)) {
				if (&first == &last) {
					delete &first;
				} else {
					delete &first;
					delete &last;
				}
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(SubMatrix&, SubMatrix&, MatrixCombinationType)\n"
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
				if (&first == &last) {
					delete &first;
				} else {
					delete &first;
					delete &last;
				}
				return outMatrix;
			}
			break;
		default:
			if (&first == &last) {
				delete &first;
			} else {
				delete &first;
				delete &last;
			}
			throw "ERROR:  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(SubMatrix&, SubMatrix&, MatrixCombinationType)\n"
				  "\tUnsupported MatrixCombinationType";
	}
}

// Build a new Matrix by multiplying two matrices together.
// @param const Matrix& left - the left Matrix in the multiplication
// @param const Matrix& right - the right Matrix in the multiplication
// @return - a new Matrix from the multiplication of the other two
// @throws exceptions for mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix& left, const Matrix& right) {
	if (left.size(2) != right.size(1)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix&, const Matrix&)\n"
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

// Build a new Matrix by multiplying a matrix with a submatrix
// @param const Matrix& left - the left Matrix in the multiplication
// @param const SubMatrix& right - the right SubMatrix in the multiplication
// @return - a new Matrix from the multiplication of the other two
// @throws exceptions for mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix& left, const SubMatrix& right) {
	if (left.size(2) != right.size(1)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const Matrix&, const SubMatrix&)\n"
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

// Build a new Matrix by multiplying a submatrix with a matrix.
// @param const Matrix& left - the left SubMatrix in the multiplication
// @param const Matrix& right - the right Matrix in the multiplication
// @return - a new Matrix from the multiplication of the other two
// @throws exceptions for mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix& left, const Matrix& right) {
	if (left.size(2) != right.size(1)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix&, const Matrix&)\n"
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

// Build a new Matrix by multiplying two submatrices together
// @param const SubMatrix& left - the left SubMatrix in the multiplication
// @param const SubMatrix& right - the right SubMatrix in the multiplication
// @return - a new Matrix from the multiplication of the other two
// @throws exceptions for mismatched dimensions.
Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix& left, const SubMatrix& right) {
	if (left.size(2) != right.size(1)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::BuildMatrixFromMultiplication(const SubMatrix&, const SubMatrix&)\n"
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

Matrix& MatrixBuilder::BuildMatrixFromAddition(const Matrix& left, const Matrix& right) {
	if (left.size(1) != right.size(1) || left.size(2) != right.size(2)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::BuildMatrixFromAddition(const Matrix&, const Matrix&)\n"
			  "\tInput Matrices must have compatible dimensions for Matrix Addition.";
	} else {
		Matrix& outMatrix = *(new Matrix(left));
		for (int i = 0; i < left.size(1); ++i) {
			for (int j = 0; j < left.size(2); ++j) {
				outMatrix(i,j) += right(i,j);
			}
		}
		return outMatrix;
	}
}

Matrix& MatrixBuilder::BuildMatrixFromSubtraction(const Matrix& left, const Matrix& right) {
	if (left.size(1) != right.size(1) || left.size(2) != right.size(2)) {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::BuildMatrixFromSubtraction(const Matrix&, const Matrix&)\n"
			  "\tInput Matrices must have compatible dimensions for Matrix Subtraction.";
	} else {
		Matrix& outMatrix = *(new Matrix(left));
		for (int i = 0; i < left.size(1); ++i) {
			for (int j = 0; j < left.size(2); ++j) {
				outMatrix(i,j) -= right(i,j);
			}
		}
		return outMatrix;
	}
}

Matrix& MatrixBuilder::SumReduce(const Matrix& mat, int dim) {
	int nRows = mat.size(1);
	int nCols = mat.size(2);
	if (dim == 1) {
		Matrix& outMatrix = *(new Matrix(1, nCols));
		for (int j = 0; j < nCols; ++j) {
			for (int i = 0; i < nRows; ++i) {
				outMatrix(0,j) += mat(i,j);
			}
		}
		return outMatrix;
	} else if (dim == 2) {
		Matrix& outMatrix = *(new Matrix(nRows, 1));
		for (int i = 0; i < nRows; ++i) {
			for (int j = 0; j < nCols; ++j) {
				outMatrix(i,0) += mat(i,j);
			}
		}
		return outMatrix;
	} else {
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::SumReduce(const Matrix&, int)\n"
			  "\tWe only support Matrix reduction with the first or second dimension.";
	}
}

Matrix& MatrixBuilder::ElementMultiply(SubMatrix& left, const Matrix& right) {
	if (left.size(1) != right.size(1) || left.size(2) != right.size(2)) {
		delete &left;
		throw "ERROR:  "
			  "Matrix& MatrixBuilder::ElementMultiply(SubMatrix&, const Matrix&)\n"
			  "\tInput Matrices must have compatible dimensions for Matrix element-wise multiplication.";
	} else {
		Matrix& outMatrix = *(new Matrix(left));
		for (int i = 0; i < right.size(1); ++i) {
			for (int j = 0; j < right.size(2); ++j) {
				outMatrix(i,j) *= right(i,j);
			}
		}
		return outMatrix;
	}
}




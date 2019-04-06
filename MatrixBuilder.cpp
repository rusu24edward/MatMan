
#include "MatrixBuilder.h"

// Build a new Matrix by combining two others according to specification.
// @param const Matrix& first - the first Matrix involved in the combination
// @param const Matrix& last - the second Matrix involved in the combination
// @param MatrixCombinatoinType rule - specify how the Matrices will be combined:
//									   (1) LeftRight
//									   (2) TopDown
// @throws exceptions for unsupported MatrixCombinationType and mismatched dimensions.
Matrix MatrixBuilder::BuildMatrixFromCombination(
		const Matrix& first, const Matrix& last, MatrixCombinationType rule) {
	switch (rule) {
		case LeftRight:
			if (first.size(1) != last.size(1)) {
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tInpt Matrices must have the same number of rows for LeftRight Matrix Combination";
			} else {
				int nRows = first.size(1);
				int nColsLeft = first.size(2);
				int nColsRight = last.size(2);
				vector<vector<double>> helper(nRows, vector<double>(nColsLeft + nColsRight));
				for (int i = 0; i < nRows; ++i) {
					for (int j = 0; j < nColsLeft; ++j) {
						helper[i][j] = first(i, j);
					}
					for (int j = 0; j < nColsRight; ++j) {
						helper[i][j + nColsLeft] = last(i, j);
					}
				}
				return *(new Matrix(helper));
			}
			break;
		case TopDown:
			if (first.size(2) != last.size(2)) {
				throw "ERROR  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tInpt Matrices must have the same number of columns for TopDown Matrix Combination";
			} else {
				int nCols = first.size(2);
				int nRowsTop = first.size(1);
				int nRowsDown = last.size(1);
				vector<vector<double>> helper(nRowsTop + nRowsDown, vector<double>(nCols));
				for (int i = 0; i < nRowsTop; ++i) {
					for (int j = 0; j < nCols; ++j) {
						helper[i][j] = first(i, j);
					}
				}
				for (int i = 0; i < nRowsDown; ++i) {
					for (int j = 0; j < nCols; ++j) {
						helper[i + nRowsTop][j] = last(i, j);
					}
				}
				return *(new Matrix(helper));
			}
			break;
		default:
			throw "ERROR:  "
				  "Matrix MatrixBuilder::BuildMatrixFromCombination(const Matrix&, const Matrix&, MatrixCombinationType)\n"
				  "\tUnsupported MatrixCombinationType";
	}
}

// Matrix MatrixBuilder::BuildMatrixFromCombination(
// 	const Matrix& first, const SubMatrix& last, MatrixCombinationType rule);
// Matrix MatrixBuilder::BuildMatrixFromCombination(
// 	const SubMatrix& first, const Matrix& last, MatrixCombinationType rule);
// Matrix MatrixBuilder::BuildMatrixFromCombination(
// 	const SubMatrix& first, const SubMatrix& last, MatrixCombinationType rule);

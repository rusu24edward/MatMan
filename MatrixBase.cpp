
#include "MatrixBase.h"

int MatrixBase::size(int dim) const {
	if (dim == 1) {
		return nRows;
	} else if (dim == 2) {
		return nCols;
	} else {
		return nRows > nCols ? nRows : nCols;
	}
}

double& MatrixBase::operator()(int r_, int c_) {
	if (r_ >= nRows || c_ >= nCols || r_ < 0 || c_ < 0) {
		throw "ERROR:  "
			  "double& MatrixBase::operator()(int, int)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	int r = r_ + top;
	int c = c_ + left;
	return data[r][c];
}

const double& MatrixBase::operator()(int r_, int c_) const {
	if (r_ >= nRows || c_ >= nCols || r_ < 0 || c_ < 0) {
		throw "ERROR:  "
			  "const double& MatrixBase::operator()(int, int) const\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	int r = r_ + top;
	int c = c_ + left;
	return data[r][c];
}





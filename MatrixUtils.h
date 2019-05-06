
#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include "Matrix.h"
#include "SubMatrix.h"
#include "MatrixBuilder.h"

Matrix& operator*(double scale, const MatrixBase& RHS) {
	return MatrixBuilder::Multiply(RHS, scale);
}

Matrix& operator*(double scale, SubMatrix& RHS) {
	return MatrixBuilder::Multiply(RHS, scale);
}

#endif

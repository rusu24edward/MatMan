
#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include "Matrix.h"
#include "MatrixBuilder.h"

Matrix& operator*(double scale, const Matrix& RHS) {
 	return MatrixBuilder::BuildMatrixFromMultiplication(RHS, scale);
}

#endif

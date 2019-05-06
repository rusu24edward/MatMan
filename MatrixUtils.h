
#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include "Matrix.h"
#include "MatrixBuilder.h"

#include <iostream>

Matrix& operator*(double scale, const MatrixBase& RHS) {
	return MatrixBuilder::Multiply(RHS, scale);
}

#endif

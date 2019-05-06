
#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H

#include <vector>

#include "MatrixBase.h"
#include "Matrix.h"
#include "SubMatrix.h" // Remove this?

#include "Enums.h"

class MatrixBuilder {

public:
	static Matrix& Combine(const MatrixBase&, const MatrixBase&, MatrixCombinationType);
	static Matrix& Multiply(const MatrixBase&, const MatrixBase&);
	static Matrix& Multiply(const MatrixBase&, double);
	static Matrix& ElementMultiply(const MatrixBase&, const MatrixBase&);

	// static Matrix& BuildMatrixFromMultiplication(const Matrix&, const Matrix&);
	// static Matrix& BuildMatrixFromMultiplication(const Matrix&, const SubMatrix&);
	// static Matrix& BuildMatrixFromMultiplication(const SubMatrix&, const Matrix&);
	// static Matrix& BuildMatrixFromMultiplication(const SubMatrix&, const SubMatrix&);
	// static Matrix& BuildMatrixFromAddition(const Matrix&, const Matrix&);
	// static Matrix& BuildMatrixFromSubtraction(const Matrix&, const Matrix&);
	// static Matrix& SumReduce(const Matrix&, int dim = 1);
	// static Matrix& Transpose(const Matrix&);

};

#endif

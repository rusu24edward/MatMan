
#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H

#include <vector>

#include "Matrix.h"
#include "SubMatrix.h"

#include "Enums.h"

class MatrixBuilder {

public:
	static Matrix& BuildMatrixFromCombination(
		const Matrix&, const Matrix&, MatrixCombinationType);
	static Matrix& BuildMatrixFromCombination(
		const Matrix&, SubMatrix&, MatrixCombinationType);
	static Matrix& BuildMatrixFromCombination(
		SubMatrix&, const Matrix&, MatrixCombinationType);
	static Matrix& BuildMatrixFromCombination(
		SubMatrix&, SubMatrix&, MatrixCombinationType);
	static Matrix& BuildMatrixFromMultiplication(const Matrix&, const Matrix&);
	static Matrix& BuildMatrixFromMultiplication(const Matrix&, const SubMatrix&);
	static Matrix& BuildMatrixFromMultiplication(const SubMatrix&, const Matrix&);
	static Matrix& BuildMatrixFromMultiplication(const SubMatrix&, const SubMatrix&);
	static Matrix& BuildMatrixFromAddition(const Matrix&, const Matrix&);
	static Matrix& BuildMatrixFromSubtraction(const Matrix&, const Matrix&);
	static Matrix& SumReduce(const Matrix&, int dim = 1);
	static Matrix& ElementMultiply(SubMatrix&, const Matrix&);
};

#endif

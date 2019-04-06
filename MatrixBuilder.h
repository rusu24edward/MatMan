
#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H

#include <vector>

#include "Matrix.h"
#include "SubMatrix.h"

#include "Enums.h"

class MatrixBuilder {

public:
	static Matrix BuildMatrixFromCombination(
		const Matrix&, const Matrix&, MatrixCombinationType);
	static Matrix BuildMatrixFromCombination(
		const Matrix&, SubMatrix&, MatrixCombinationType);
	// static Matrix BuildMatrixFromCombination(
	// 	const SubMatrix&, const Matrix&, MatrixCombinationType);
	// static Matrix BuildMatrixFromCombination(
	// 	const SubMatrix&, const SubMatrix&, MatrixCombinationType);
};

#endif


#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <iostream>
#include <fstream>

#include "MatrixBase.h"
#include "Matrix.h"
class Matrix;

using namespace std;

class SubMatrix : public MatrixBase {

friend class Matrix;

public:

	// --- Destructor --- //
	~SubMatrix();

	// --- Functions and Operators --- //
	void operator=(const Matrix&);
	void operator=(SubMatrix&);
	void operator=(double);
	Matrix& operator*(const Matrix&);
	Matrix& operator*(SubMatrix&);


private:

	// --- Constructors --- //
	SubMatrix(vector<vector<double>>*, int, int, int, int);

};

#endif

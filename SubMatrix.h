
#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <iostream>
#include <fstream>

#include "Matrix.h"
class Matrix;

using namespace std;

class SubMatrix {

friend class Matrix;

public:

	// --- Destructor --- //
	~SubMatrix();

	// --- Functions and Operators --- //
	void operator=(const Matrix&);
	void operator=(SubMatrix&);
	void operator=(double);
	double& operator()(int, int);
	const double& operator()(int, int) const;
	int size(int dim = 0) const;
	Matrix& operator*(const Matrix&);
	Matrix& operator*(SubMatrix&);

	// --- Printing --- //
	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const SubMatrix&);
	void Print(fstream&) const;
	friend ofstream& operator<<(ofstream&, const SubMatrix&);

private:

	// --- Constructors --- //
	SubMatrix(Matrix*, int, int, int, int);

	// --- Underlying Data --- //
	Matrix* data;
	int left, right, top, down;
	int nRows, nCols;

};

#endif

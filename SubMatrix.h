
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

	// --- Functions and Operators --- //
	void operator=(const Matrix&);
	void operator=(SubMatrix&);
	void operator=(double);
	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const SubMatrix&);
	void Print(fstream&) const;
	friend ofstream& operator<<(ofstream&, const SubMatrix&);

private:

	// --- Constructors --- //
	SubMatrix(Matrix*, int, int, int, int);

	// --- Destructor --- //
	~SubMatrix();

	// --- Underlying Data --- //
	Matrix* data;
	int left, right, top, down;
	int nRows, nCols;

};

#endif

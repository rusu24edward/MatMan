
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "MatrixBase.h"
#include "NamedObject.h"
#include "SubMatrix.h"
class SubMatrix;

using namespace std;

// Matrix class provides data storage and manipulation like a mathematical matrix.
// Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
//		- Generate matrices from vector<vector<double>>
//		- Extract value from index
//		- Insert value at index
//		- Set all elements to a number
//		- Extract SubMatrices
//		- Construct new Matrices from SubMatrices
//		- Query the matrix size
class Matrix : public NamedObject, public MatrixBase {

public:

	// --- Constructors --- //
	Matrix();
	Matrix(int, int);
	Matrix(int, int, double);
	Matrix(const vector<vector<double>>&);
	Matrix(const Matrix&);
	Matrix(SubMatrix&);

	// --- Destructor --- //
	~Matrix();

	// --- Assignment Operators --- //
	Matrix& operator=(const vector<vector<double>>&);
	Matrix& operator=(const Matrix&);
	Matrix& operator=(SubMatrix&);

	// --- Accessors & Mutators --- //
	const string& getName() const;
	void setName(const string&);

	// --- Functions and Operators --- //
	SubMatrix& operator()(int, int, int, int);
	double& operator()(int, int);


private:

	// --- Helper Functions --- //
	void setFields(int r = 0, int c = 0, double value = 0);
	void setFields(const vector<vector<double>>&);
	void setFields(const Matrix&);
	void setFields(SubMatrix&);
	void deleteFields();
	bool checkCols(const vector<vector<double>>&);


	// --- Underlying Data --- //
	vector<vector<double>> data;
};

#endif

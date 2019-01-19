
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

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
class Matrix {
public:

	typedef Matrix* SubMatrix;

	// -------------------- //
	// --- Constructors --- //
	// -------------------- //

	Matrix();
	Matrix(int, int);
	Matrix(int, int, double);
	Matrix(const vector<vector<double>>&);
	Matrix(const Matrix&);
	Matrix(SubMatrix);



	// ------------------ //
	// --- Destructor --- //
	// ------------------ //

	~Matrix();



	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //

	Matrix& operator=(const Matrix&);
	Matrix& operator=(SubMatrix);
	Matrix& operator=(const vector<vector<double>>&);



	// ---------------------------- //
	// --- Accessors & Mutators --- //
	// ---------------------------- //

	// -- Matrix Name --- //
	const string& getName() const;
	void setName(const string&);



	// ------------------------------- //
	// --- Functions and Operators --- //
	// ------------------------------- //

	// --- Element insertion and extraction --- //
	const double extract(int, int) const;
	const double operator()(int, int) const;
	void insert(int, int, double);
	void insert(double);
	void operator=(double);

	// --- Submatrix Extraction --- //
	SubMatrix extract(int, int, int, int) const;
	SubMatrix operator()(int, int, int, int) const;

	// --- Matrix Stucture --- //
	vector<int> size();
	int size(int);
	int length();



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const Matrix&);
	void Print(ofstream&) const;
	friend ofstream& operator<<(ofstream&, const Matrix&);

	// --- DEBUG FUNCTION --- //
	void DEBUG_PrintFromLimits() const;





private:

	// ------------------------ //
	// --- Helper Functions --- //
	// ------------------------ //

	// --- Object Construction Helpers --- //
	void setFields(int r = 0, int c = 0, double value = 0);
	void setLimitsToData();



	// ----------------------- //
	// --- Underlying Data --- //
	// ----------------------- //

	string name;
	const string UNAMED = "UNAMED";

	int nRows;
	int nCols;
	vector<vector<double>> data;
};

#endif

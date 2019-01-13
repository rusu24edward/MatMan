
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include "SubMatrix.h"

using namespace std;

// Matrix class provides data storage and manipulation like a mathematical matrix.
// Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
//		- Generate matrices from vector<vector<double>>
//		- Extract value from index
//		- Insert value at index
//		- Set all elements to a number
class Matrix {
public:

	// typedef vector<double>::const_iterator vdc_iterator;

	// -------------------- //
	// --- Constructors --- //
	// -------------------- //

	// Default constructor sets the fields to their default states
	Matrix() {
		setFields();
		name = UNAMED;
	}

	// Alternate constructor sets the number of rows and columns and builds a
	// matrix of appropriate size.
	// @param int r - the number of rows
	// @param int c - the number of columns
	Matrix(int r, int c) {
		setFields(r, c);
		name = UNAMED;
	}

	// Alternate constructor sets the number of rows and columns and fills an
	// appropriately sized matrix with the specified value
	// @param int r - the number of rows
	// @param int c - the number of columns
	// @param double value - set each element in the matrix to this value
	Matrix(int r, int c, double value) {
		setFields(r, c, value);
		name = UNAMED;
	}

	// Alternate constructor converts the input vector of vectors of doubles to a
	// Matrix.
	// @param const vector<vector<double>>& d - this Matrix's data
	Matrix(const vector<vector<double>>& d) {
		int checkNumberOfColumns = d[0].size();
		for (int i = 1; i < d.size(); ++i) {
			if (d[i].size() != checkNumberOfColumns) {
				throw "ERROR:  "
					  "Matrix::Matrix(const vector<vector<double>>&)\n"
					  "\tInconsistent number of columns in input argument.";

			}
		}

		setFields(d.size(), checkNumberOfColumns);
		name = UNAMED;
		data = d;
	}

	// Copy constructor copies the input Matrix.
	// @param const Matrix& mat - Matrix from which to copy
	Matrix(const Matrix& mat) {
		setFields(mat.nRows, mat.nCols);
		name = UNAMED;
		data = mat.data;
	}



	// ------------------ //
	// --- Destructor --- //
	// ------------------ //

	// Destructor sets all fields to their default states and removes the name
	~Matrix() {
		setFields();
		name = "";
	}



	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //

	// Assignemnt operator blows out the Matrix data and sets it to the RHS
	// @param const Matrix& mat - Matrix to copy
	// @return Matrix& - this Matrix
	Matrix& operator=(const Matrix& mat) {
		if (this != &mat) {
			setFields(mat.nRows, mat.nCols);
			data = mat.data;
		}
		return *this;
	}

	// Assignment operator blows out the Matrix and replace it with the input vector
	// @param const vector<vector<double>>& d - copy the data
	// @return Matrix& - this Matrix
	Matrix& operator=(const vector<vector<double>>& d) {
		int checkNumberOfColumns = d[0].size();
		for (int i = 1; i < d.size(); ++i) {
			if (d[i].size() != checkNumberOfColumns) {
				throw "ERROR:  "
					  "Matrix& Matrix::operator=(const vector<vector<double>>&)\n"
					  "\tInconsistent number of columns in input argument.";
			}
		}

		setFields(d.size(), checkNumberOfColumns);
		data = d;

		return *this;
	}



	// ---------------------------- //
	// --- Accessors & Mutators --- //
	// ---------------------------- //

	// -- Matrix Name --- //

	// Get the name of the Matrix
	// @return const string& - the Matrix's name
	const string& getName() const {
		return name;
	}

	// Set the name of the Matrix
	// @param const string& n - the Matrix's name
	void setName(const string& n) {
		name = n;
	}


	// ------------------------------- //
	// --- Functions and Operators --- //
	// ------------------------------- //

	// --- Element insertion and extraction --- //

	// Extract the value at the specified index
	// @param int r - the row index
	// @param int c - the column index
	// @return const double - the value at this index
	const double extract(int r, int c) const {
		if (r >= nRows || c >= nCols || r < 0 || c < 0) {
			throw "ERROR:  "
				  "const double Matrix::extract(int, int) const\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}
	const double operator()(int r, int c) const {
		if (r >= nRows || c >= nCols || r < 0 || c < 0) {
			throw "ERROR:  "
				  "const double Matrix::operator()(int, int) const\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}

	// Insert specified value at specified index
	// @param int r - the row index
	// @param int c - the column index
	// @param double value - the value to insert at the index
	void insert(int r, int c, double value) {
		if (r >= nRows || c >= nCols || r < 0 || c < 0) {
			throw "ERROR:  "
				  "void Matrix::insert(int, int, double)\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		data[r][c] = value;
	}

	// Insert a value to all elements of the Matrix
	// @param double value - the value to insert
	void insert(double value) {
		for (int i = 0; i < nRows; ++i) {
			for (int j = 0; j < nCols; ++j) {
				data[i][j] = value;
			}
		}
	}
	void operator=(double value) {
		for (int i = 0; i < nRows; ++i) {
			for (int j = 0; j < nCols; ++j) {
				data[i][j] = value;
			}
		}
	}

	// --- Submatrix Insertion and Extraction --- //

	// SubMatrix& extract(int t, int b, int l, int r) {
	// 	if (t < 0 || b >= nRows || l < 0 || r >= nCols) {
	// 		throw "ERROR:  "
	// 			  "Submatrix& Matrix::extract(int, int, int, int)\n"
	// 			  "\tAttempting to access elements outside the matrix range.";
	// 	}
	// 	if (b < t || r < l) {
	// 		throw "ERROR:  "
	// 			  "SubMatrix& Matrix::extract(int, int, int, int)\n"
	// 			  "\tIndices are not ordered correctly.";
	// 	}
	// 	setSubMatrixToLimits(t, b, l, r);

	// 	return submatrix;
	// }



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	// Print to an ostream
	// @param ostream& streamer - print to this ostream
	void Print(ostream& streamer) const {
		streamer << endl << name << endl;
		streamer << "\tRows: " << nRows << endl;
		streamer << "\tCols: " << nCols << endl;
		for (vector<vector<double>>::const_iterator
			 i = data.begin(); i != data.end(); ++i) {
			streamer << "\t\t[ ";
			for (vector<double>::const_iterator
				 j = i->begin(); j != i->end(); ++j) {
				streamer << *j << " ";
			}
			streamer << "]" << endl;
		}
	}
	friend ostream& operator<<(ostream& streamer, const Matrix& mat) {
		mat.Print(streamer);
		return streamer;
	}

	// Print to an ofstream
	// @param ofstream& fileOut - print to this ofstream
	void Print(ofstream& fileOut) const {
		fileOut << endl << name << endl;
		fileOut << "\tRows: " << nRows << endl;
		fileOut << "\tCols: " << nCols << endl;
		for (vector<vector<double>>::const_iterator
			 i = data.begin(); i != data.end(); ++i) {
			fileOut << "\t\t[ ";
			for (vector<double>::const_iterator
				 j = i->begin(); j != i->end(); ++j) {
				fileOut << *j << " ";
			}
			fileOut << "]" << endl;
		}
	}
	friend ofstream& operator<<(ofstream& fileOut, const Matrix& mat) {
		mat.Print(fileOut);
		return fileOut;
	}

	// --- DEBUG FUNCTION --- //
	// void DEBUG_PrintFromLimits() const {
	// 	cout << "PrintFromLimits" << endl;
	// 	for (vector<pair<SubMatrix::vd_iter, SubMatrix::vd_iter>>::const_iterator
	// 			i = submatrix.limits.begin(); i != submatrix.limits.end(); ++i) {
	// 		cout << "\t\t[ ";
	// 		for (SubMatrix::vd_iter j = i->first; j != i->second; ++j) {
	// 			cout << *j << " ";
	// 		}
	// 		cout << "]" << endl;
	// 	}
	// }





private:

	// ------------------------ //
	// --- Helper Functions --- //
	// ------------------------ //

	// --- Object Construction Helpers --- //

	// Set the class fields
	// @param int r - the number of rows
	// @param int c - the number of columns
	// @param double value - set each element in the matrix to this value
	void setFields(int r = 0, int c = 0, double value = 0.0) {
		// write a check here for the parameters. e.g. r >= 0
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, value));
		// setSubMatrixToData();
	}

	// Set the pointers in limits to the beginning and end of each row of data
	// void setSubMatrixToData() {
	// 	submatrix.limits.clear();
	// 	for (vector<vector<double>>::iterator
	// 			i = data.begin(); i != data.end(); ++i) {
	// 		submatrix.limits.push_back(pair<SubMatrix::vd_iter, SubMatrix::vd_iter>(i->begin(), i->end()));
	// 	}
	// }


	// void setSubMatrixToLimits(int t, int b, int l, int r) {
	// 	submatrix.limits.clear();
	// 	for (vector<vector<double>>::iterator
	// 			i = data.begin() + t; i != data.end() + b; ++i) {
	// 		submatrix.limits.push_back(pair<SubMatrix::vd_iter, SubMatrix::vd_iter>(i->begin() + l, i->end() + r));
	// 	}
	// }



	// ----------------------- //
	// --- Underlying Data --- //
	// ----------------------- //

	string name;
	const string UNAMED = "UNAMED";

	int nRows;
	int nCols;
	vector<vector<double>> data;

	// SubMatrix submatrix;

};

#endif

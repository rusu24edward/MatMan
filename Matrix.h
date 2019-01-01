
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Matrix class provides data storage and manipulation like a mathematical matrix.
// Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
//		- Generate matrices from vector<vector<double>>
//		- Extract value from index
//		- Insert value at index
class Matrix {
public:

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

	// Copy constructor copies values between the input Matrix's limits.
	// @param const Matrix& mat - Matrix from which to copy
	Matrix(const Matrix& mat) {
		setFields(mat.bottomLimit - mat.topLimit, mat.rightLimit - mat.leftLimit);
		name = UNAMED;
		copyBetweenLimits(mat);
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
			setFields(mat.bottomLimit - mat.topLimit, mat.rightLimit - mat.leftLimit);
			copyBetweenLimits(mat);
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
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR:  "
				  "const double Matrix::extract(int, int) const\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}
	const double operator()(int r, int c) const {
		if (r >= bottomLimit || c >= rightLimit) {
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
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR:  "
				  "void Matrix::insert()(int, int, double)\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		data[r][c] = value;
	}
	// In order to make this function happen, I need to setup iterators that point
	// to a specific location or a range of locations (including the entire thing)
	// that need to be updated.
	// TODO: implement iterators
	// void insert(double value) {
		// insert the value at the location of the iterators.
	//}
	// void operator=(double value) {
		// insert the value at the location of the iterators.
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
		streamer << "\tIterators: (" << topLimit << ", " << bottomLimit << ", "
			 << leftLimit << ", " << rightLimit << ")" << endl;
	}
	friend ostream& operator<<(ostream& streamer, const Matrix& mat) {
		mat.Print(streamer);
		return streamer;
	}

	// Print to an fstream
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
		fileOut << "\tIterators: (" << topLimit << ", " << bottomLimit << ", "
			 << leftLimit << ", " << rightLimit << ")" << endl;
	}
	friend ofstream& operator<<(ofstream& fileOut, const Matrix& mat) {
		mat.Print(fileOut);
		return fileOut;
	}





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

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;
	}

	// Copy values between input Matrix's limit
	// @param const Matrix& mat - Matrix from which to copy
	void copyBetweenLimits(const Matrix& mat) {
		for (int i = topLimit, ii = mat.topLimit; i < bottomLimit; ++i, ++ii) {
			for (int j = leftLimit, jj = mat.leftLimit; j < rightLimit; ++j, ++jj) {
				data[i][j] = mat.extract(ii, jj);
			}
		}
	}



	// ----------------------- //
	// --- Underlying Data --- //
	// ----------------------- //

	string name;
	const string UNAMED = "UNAMED";

	int nRows;
	int nCols;
	vector<vector<double>> data;

	int topLimit;
	int bottomLimit;
	int leftLimit;
	int rightLimit;

};

#endif

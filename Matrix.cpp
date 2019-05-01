
#include "Matrix.h"

#include <math.h>

// #include "MatrixBuilder.h"


using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Default constructor sets the fields to their default states
Matrix::Matrix() {
	setFields();
	name = UNAMED;
}

// Alternate constructor sets the number of rows and columns and builds a
// matrix of appropriate size.
// @param int r - the number of rows
// @param int c - the number of columns
Matrix::Matrix(int r, int c) {
	setFields(r, c);
	name = UNAMED;
}

// Alternate constructor sets the number of rows and columns and fills an
// appropriately sized matrix with the specified value
// @param int r - the number of rows
// @param int c - the number of columns
// @param double value - set each element in the matrix to this value
Matrix::Matrix(int r, int c, double value) {
	setFields(r, c, value);
	name = UNAMED;
}

// Alternate constructor converts the input vector of vectors of doubles to a
// Matrix.
// @param const vector<vector<double>>& d - this Matrix's data
Matrix::Matrix(const vector<vector<double>>& d) {
	if (!checkCols(d)) {
		throw "ERROR:  "
			  "Matrix::Matrix(const vector<vector<double>>&)\n"
			  "\tInconsistent number of columns in input argument.";
	}
	setFields(d);
	name = UNAMED;
}

// Copy constructor copies the input Matrix.
// @param const Matrix& mat - Matrix from which to copy
Matrix::Matrix(const Matrix& mat) {
	setFields(mat);
	name = UNAMED;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all fields to their default states and removes the name
Matrix::~Matrix() {
	deleteFields();
	name = "";
}



// ---------------------------- //
// --- Assignment Operators --- //
// ---------------------------- //

// Assignment operator blows out the Matrix and replace it with the input vector
// @param const vector<vector<double>>& d - vector from which to copy
// @return Matrix& - this Matrix
Matrix& Matrix::operator=(const vector<vector<double>>& d) {
	if (!checkCols(d)) {
		throw "ERROR:  "
			  "Matrix& Matrix::operator=(const vector<vector<double>>&)\n"
			  "\tInconsistent number of columns in input argument.";
	}
	deleteFields();
	setFields(d);
	return *this;
}

// Assignemnt operator blows out the Matrix and sets it to the RHS
// @param const Matrix& mat - Matrix from which to copy
// @return Matrix& - this Matrix
Matrix& Matrix::operator=(const Matrix& mat) {
	if (this != &mat) {
		deleteFields();
		setFields(mat);
	}
	return *this;
}




// ---------------------------- //
// --- Accessors & Mutators --- //
// ---------------------------- //

// -- Matrix Name --- //

// Get the name of the Matrix
// @return const string& - the Matrix's name
const string& Matrix::getName() const {
	return name;
}

// Set the name of the Matrix
// @param const string& n - the Matrix's name
void Matrix::setName(const string& n) {
	name = n;
}





// ------------------------ //
// --- Helper Functions --- //
// ------------------------ //

// --- Object Construction Helpers --- //

// Set the class fields
// @param int r - the number of rows
// @param int c - the number of columns
// @param double value - set each element in the matrix to this value
void Matrix::setFields(int r, int c, double value) {
	nRows = r;
	nCols = c;
	top = left = 0;
	down = nRows;
	right = nCols;
	data = vector<vector<double>>(r, vector<double>(c, value));
	data_ptr = &data;
}

// Set the class fields
// @param const vector<vector<double>>& d - the input vector from which to copy
void Matrix::setFields(const vector<vector<double>>& d) {
	data = d;
	data_ptr = &data;
	nRows = data.size();
	nCols = data[0].size();
	top = left = 0;
	down = nRows;
	right = nCols;
}

// Set the class fields
// @param const Matrix& mat - the input Matrix from which to copy
void Matrix::setFields(const Matrix& mat) {
	data = mat.data;
	data_ptr = &data;
	nRows = data.size();
	nCols = data[0].size();
	top = left = 0;
	down = nRows;
	right = nCols;
}

// Delete the class fields
void Matrix::deleteFields() {
	data_ptr = 0;
	data.clear();
	nRows = nCols = top = down = left = right = 0;
}

// Check that the number of elements in each vector is the same
// @param const vector<vector<double>>& - input vector of vectors
// @return bool - true if they're all the same, false otherwise.
bool Matrix::checkCols(const vector<vector<double>>& d) {
	int checkNumberOfColumns = d[0].size();
	for (int i = 1; i < d.size(); ++i) {
		if (d[i].size() != checkNumberOfColumns) {
			return false;
		}
	}
	return true;
}


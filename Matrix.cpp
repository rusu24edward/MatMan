
#include "Matrix.h"
#include <math.h>

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

// Copy constructor copies the input SubMatrix
// @param SubMatrix& sm - input SubMatrix from which to copy
Matrix::Matrix(SubMatrix& sm) {
	setFields(sm);
	name = UNAMED;
	delete &sm;
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

// Assignemnt operator blows out the Matrix and sets it to the RHS
// @param SubMatrix& sm - SubMatrix frrom which to copy
// @return Matrix& - this Matrix
Matrix& Matrix::operator=(SubMatrix& sm) {
	deleteFields();
	setFields(sm);
	delete &sm;
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



// ------------------------------- //
// --- Functions and Operators --- //
// ------------------------------- //

// --- Element support --- //

// Extract the value at the specified index
// @param int r - the row index
// @param int c - the column index
// @return double& - the value at this index
double& Matrix::operator()(int r, int c) {
	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
		throw "ERROR:  "
			  "double& Matrix::operator()(int, int)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	return data[r][c];
}
const double& Matrix::operator()(int r, int c) const {
	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
		throw "ERROR:  "
			  "double& Matrix::operator()(int, int)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	return data[r][c];
}

// Set the entire Matrix equal to the input value
// @param double value - the value to insert
void Matrix::operator=(double value) {
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			data[i][j] = value;
		}
	}
}


// --- SubMatrix Support --- //

// Generate a SubMatrix from this Matrix using the indicies
// @param int top - top index
// @param int down - bottom index
// @param int left - left index
// @param int right - right index
// @return SubMatrix& - the SubMatrix
SubMatrix& Matrix::operator()(int top, int down, int left, int right) {
	if (down < top || right < left) {
		throw "ERROR:  "
			  "SubMatrix& Matrix::operator()(int, int, int, int)\n"
			  "\tUnordered Range.";
	}
	if (top < 0 || down >= nRows || left < 0 || right >= nCols) {
		throw "ERROR:  "
			  "SubMatrix& Matrix::operator()(int, int, int, int)\n"
			  "\tAttempting to access elements outside the Matrix range.";
	}
	return *(new SubMatrix(this, top, down, left, right));
}


// --- Query Support --- //

// Return the length of the greater dimension
int Matrix::length() const {
	return nRows > nCols ? nRows : nCols;
}

// Return the size of the specified dimension.
// @param int dim - if 1, then return nRows
//				  - if 2, then return nCols
//				  - else, return the larger length
// @return int - the length
int Matrix::size(int dim) const {
	if (dim == 1) {
		return nRows;
	} else if (dim == 2) {
		return nCols;
	} else {
		return length();
	}
}


// --- Mathematical operation support --- //

// Calculate the vector 2-norm of this Matrix.
// @return double - the vector 2-norm of this Matrix.
// throws an error if the Matrix is not a vector
double Matrix::norm() const {
	if (nRows != 1 && nCols != 1) {
		throw "ERROR:  "
			  "double Matrix::norm() const\n"
			  "You are asking for the norm of a matrix, but we only support the 2-norm of a vector.";
	} else if (nRows == 1 && nCols == 1) {
		return data[0][0];
	} else if (nRows == 1 && nCols != 1) {
		double norm2 = 0.0;
		for (int n = 0; n < nCols; ++n) {
			norm2 += pow(data[0][n], 2);
		}
		return sqrt(norm2);
	} else { // nRows != 1 && nCols == 1
		double norm2 = 0.0;
		for (int n = 0; n < nRows; ++n) {
			norm2 += pow(data[n][0], 2);
		}
		return sqrt(norm2);
	}
}

// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void Matrix::Print(ostream& streamer) const {
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
ostream& operator<<(ostream& streamer, const Matrix& mat) {
	mat.Print(streamer);
	return streamer;
}

// Print to an fstream
// @param ofstream& fileOut - print to this ofstream
void Matrix::Print(ofstream& fileOut) const {
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
ofstream& operator<<(ofstream& fileOut, const Matrix& mat) {
	mat.Print(fileOut);
	return fileOut;
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
	data = vector<vector<double>>(r, vector<double>(c, value));
}

// Set the class fields
// @param const vector<vector<double>>& d - the input vector from which to copy
void Matrix::setFields(const vector<vector<double>>& d) {
	data = d;
	nRows = data.size();
	nCols = data[0].size();
}

// Set the class fields
// @param const Matrix& mat - the input Matrix from which to copy
void Matrix::setFields(const Matrix& mat) {
	data = mat.data;
	nRows = data.size();
	nCols = data[0].size();
}

// Set the class fields
// @param const SubMatrix& sm - the input SubMatrix from which to copy
void Matrix::setFields(SubMatrix& sm) {
	nRows = sm.nRows;
	nCols = sm.nCols;
	data = vector<vector<double>>(sm.nRows, vector<double>(sm.nCols));
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			data[i][j] = sm(i, j);
		}
	}
}

// Delete the class fields
void Matrix::deleteFields() {
	data.clear();
	nRows = nCols = 0;
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


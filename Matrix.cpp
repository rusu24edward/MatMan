
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



// ------------------------------------ //
// --- SubMatrix and Element Access --- //
// ------------------------------------ //

SubMatrix& Matrix::operator()(int _top, int _down, int _left, int _right) {
	if (_down < _top || _right < _left) {
		throw "ERROR:  "
			  "SubMatrix& Matrix::operator()(int, int, int, int)\n"
			  "\tUnordered Range.";
	}
	if (_top < 0 || _down >= nRows || _left < 0 || _right >= nCols) {
		throw "ERROR:  "
			  "SubMatrix& Matrix::operator()(int, int, int, int)\n"
			  "\tAttempting to access elements outside the Matrix range.";
	}
	return *(new SubMatrix(data_ptr, _top, _down, _left, _right));
}

double& Matrix::operator()(int r, int c) {
	return MatrixBase::operator()(r, c);
}
const double& Matrix::operator()(int r, int c) const {
	return MatrixBase::operator()(r, c);
}

void Matrix::operator=(double value) {
	MatrixBase::operator=(value);
}




// ------------------------------- //
// --- Mathematical Operations --- //
// ------------------------------- //

int Matrix::length() const {
	return nRows > nCols ? nRows : nCols;
}

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

// Construct a Matix by multipliying this Matrix with another. This lives here in order to
// overload the multiplication operator, but all the work is offloaded to MatrixBuilder.
// @param const Matrix& RHS - the RHS Matix involved in the operation
// @return Matrix& - new Matrix formed from multiplying these two.
// Matrix& Matrix::operator*(const Matrix& RHS) const {
// 	return MatrixBuilder::Multiply(*this, RHS);
// }

// Construct a Matix by multipliying this Matrix with a SubMatrix. This lives here in order to
// overload the multiplication operator, but all the work is offloaded to MatrixBuilder.
// @param SubMatrix& RHS - the RHS SubMatix involved in the operation
// @return Matrix& - new Matrix formed from multiplying these two.
// Matrix& Matrix::operator*(SubMatrix& RHS) const {
// 	Matrix& outMatrix = MatrixBuilder::Multiply(*this, RHS);
// 	delete &RHS;
// 	return outMatrix;
// }



void Matrix::Print(ostream& streamer) const {
	streamer << endl << name << endl;
	MatrixBase::Print(streamer);
}
ostream& operator<<(ostream& streamer, const Matrix& mat) {
	mat.Print(streamer);
	return streamer;
}
void Matrix::Print(ofstream& fileOut) const {
	fileOut << endl << name << endl;
	MatrixBase::Print(fileOut);
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

void Matrix::setFields(SubMatrix& sm) {
	nRows = sm.nRows;
	nCols = sm.nCols;
	data = vector<vector<double>>(sm.nRows, vector<double>(sm.nCols));
	data_ptr = &data;
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			data[i][j] = sm(i, j);
		}
	}
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


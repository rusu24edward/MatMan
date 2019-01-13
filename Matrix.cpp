
#include "Matrix.h"

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
Matrix::Matrix(const Matrix& mat) {
	setFields(mat.nRows, mat.nCols);
	name = UNAMED;
	data = mat.data;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all fields to their default states and removes the name
Matrix::~Matrix() {
	setFields();
	name = "";
}



// ---------------------------- //
// --- Assignment Operators --- //
// ---------------------------- //

// Assignemnt operator blows out the Matrix data and sets it to the RHS
// @param const Matrix& mat - Matrix to copy
// @return Matrix& - this Matrix
Matrix& Matrix::operator=(const Matrix& mat) {
	if (this != &mat) {
		setFields(mat.nRows, mat.nCols);
		data = mat.data;
	}
	return *this;
}

// Assignment operator blows out the Matrix and replace it with the input vector
// @param const vector<vector<double>>& d - copy the data
// @return Matrix& - this Matrix
Matrix& Matrix::operator=(const vector<vector<double>>& d) {
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

// --- Element insertion and extraction --- //

// Extract the value at the specified index
// @param int r - the row index
// @param int c - the column index
// @return const double - the value at this index
const double Matrix::extract(int r, int c) const {
	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
		throw "ERROR:  "
			  "const double Matrix::extract(int, int) const\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	return data[r][c];
}
const double Matrix::operator()(int r, int c) const {
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
void Matrix::insert(int r, int c, double value) {
	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
		throw "ERROR:  "
			  "void Matrix::insert()(int, int, double)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	data[r][c] = value;
}

// Insert a value to all elements of the Matrix
// @param double value - the value to insert
void Matrix::insert(double value) {
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			data[i][j] = value;
		}
	}
}
void Matrix::operator=(double value) {
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			data[i][j] = value;
		}
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

// --- DEBUG FUNCTION --- //
void Matrix::DEBUG_PrintFromLimits() const {
	cout << "PrintFromLimits" << endl;
	for (vector<pair<vdc_iterator, vdc_iterator>>::const_iterator
			i = limits.begin(); i != limits.end(); ++i) {
		cout << "\t\t[ ";
		for (vdc_iterator j = i->first; j != i->second; ++j) {
			cout << *j << " ";
		}
		cout << "]" << endl;
	}
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
	// write a check here for the parameters. e.g. r >= 0
	nRows = r;
	nCols = c;
	data = vector<vector<double>>(r, vector<double>(c, value));
	setLimitsToData();
}

// Set the pointers in limits to the beginning and end of each row of data
void Matrix::setLimitsToData() {
	limits.clear();
	for (vector<vector<double>>::const_iterator
			i = data.begin(); i != data.end(); ++i) {
		limits.push_back(pair<vdc_iterator, vdc_iterator>(i->begin(), i->end()));
	}
}












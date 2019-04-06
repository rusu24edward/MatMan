
#include "SubMatrix.h"

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Constructor sets the data and the limits
// @param Matrix* mat - the pointer to the Matrix data
// @param int _top - top index
// @param int _down - bottom index
// @param int _left - left index
// @param int _right - right index
SubMatrix::SubMatrix(Matrix* mat, int _top, int _down, int _left, int _right) {
	data = mat;
	top = _top;
	down = _down+1;
	left = _left;
	right = _right+1;
	nRows = down - top;
	nCols = right - left;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all to 0
SubMatrix::~SubMatrix() {
	data = 0;
	top = down = left = right = nRows = nCols = 0;
}



// ------------------------------- //
// --- Functions and Operators --- //
// ------------------------------- //

// Set the values to the values from the input Matrix
// @param const Matrix& mat - the input Matrix from which to copy
void SubMatrix::operator=(const Matrix& mat) {
	if (nRows != mat.size(1) || nCols != mat.size(2)) {
		throw "ERROR:  "
			  "void SubMatrix::operator=(const Matrix&)\n"
			  "\tMatrices are not the same size.";
	}

	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			this->operator()(i, j) = mat(i, j);
		}
	}

	delete this;
}

// Set the values to the values from the input SubMatrix
// @param const SubMatrix& sm - the input SubMatrix from which to copy
void SubMatrix::operator=(SubMatrix& sm) {
	if (nRows != sm.nRows || nCols != sm.nCols) {
		throw "ERROR:  "
			  "void SubMatrix::operator=(SubMatrix&)\n"
			  "\tMatrices are not the same size.";
	}

	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			this->operator()(i, j) = sm(i, j);
		}
	}

	delete this;
}

// Set the values to the input double
// @param double - set values to this double
void SubMatrix::operator=(double d) {
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			this->operator()(i, j) = d;
		}
	}

	delete this;
}

// Extract the value at the specified index of the SubMatrix.
// @param int i - the ith row
// @param int j - the jth row
// @return double& - reference to the double at the (i,j)th position of the SubMatrix.
double& SubMatrix::operator()(int i, int j) {
	return data->operator()(i + top, j + left);
}

// Return the size of the specified dimension.
// @param int dim - if 1, then return nRows
//				  - if 2, then return nCols
//				  - else, return the larger length
// @return int - the length
int SubMatrix::size(int dim) const {
	if (dim == 1) {
		return nRows;
	} else if (dim == 2) {
		return nCols;
	} else {
		return nRows > nCols ? nRows : nCols;
	}
}





// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void SubMatrix::Print(ostream& streamer) const {
	for (int i = top; i < down; ++i) {
		streamer << "\t\t[ ";
		for (int j = left; j < right; ++j) {
			streamer << data->operator()(i,j) << endl;
		}
		streamer << "]" << endl;
	}

	delete this;
}
ostream& operator<<(ostream& streamer, const SubMatrix& sm) {
	sm.Print(streamer);
	return streamer;
}

// Print to an fstream
// @param ofstream& fileOut - print to this ofstream
void SubMatrix::Print(fstream& outFile) const {
	for (int i = top; i < down; ++i) {
		outFile << "\t\t[ ";
		for (int j = left; j < right; ++j) {
			outFile << data->operator()(i,j) << endl;
		}
		outFile << "]" << endl;
	}

	delete this;
}
ofstream& operator<<(ofstream& outFile, const SubMatrix& sm) {
	sm.Print(outFile);
	return outFile;
}



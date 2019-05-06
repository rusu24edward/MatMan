
#include "SubMatrix.h"
#include "MatrixBuilder.h"

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Constructor sets the data and the limits
// @param vector<vector>* mat - the pointer to the Matrix data
// @param int _top - top index
// @param int _down - bottom index
// @param int _left - left index
// @param int _right - right index
SubMatrix::SubMatrix(vector<vector<double>>* _data_ptr, int _top, int _down, int _left, int _right) {
	data_ptr = _data_ptr;
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
	data_ptr = 0;
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
			operator()(i, j) = mat(i, j);
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
			operator()(i, j) = sm(i, j);
		}
	}

	delete &sm;
	delete this;
}

// Set the values to the input double
// @param double - set values to this double
void SubMatrix::operator=(double value) {
	MatrixBase::operator=(value);
}

// 	delete this;
// }


// // --- Mathematical Operations Support --- //

// Construct a Matrix by multiplying this SubMatrix with a Matrix. This lives here in order to
// overload the multiplication operator, but all the work is offloaded to MatrixBuilder.
// @param const MatrixBase& RHS - the RHS Matix involved in the operation
// @return Matrix& - new Matrix formed from multiplying these two.
Matrix& SubMatrix::operator*(const Matrix& RHS) {
	Matrix& outMatrix = MatrixBuilder::Multiply(*this, RHS);
	delete this;
	return outMatrix;
}

// Construct a Matix by multipliying this SubMatrix with another. This lives here in order to
// overload the multiplication operator, but all the work is offloaded to MatrixBuilder.
// @param SubMatrix& RHS - the RHS SubMatix involved in the operation
// @return Matrix& - new Matrix formed from multiplying these two.
Matrix& SubMatrix::operator*(SubMatrix& RHS) {
	Matrix& outMatrix = MatrixBuilder::Multiply(*this, RHS);
	delete &RHS;
	delete this;
	return outMatrix;
}

Matrix& SubMatrix::operator*(double RHS) {
	return MatrixBuilder::Multiply(*this, RHS);
}





// ---------------- //
// --- Printing --- //
// ---------------- //

// // Print to an ostream
// // @param ostream& streamer - print to this ostream
// void SubMatrix::Print(ostream& streamer) const {
// 	for (int i = top; i < down; ++i) {
// 		streamer << "\t\t[ ";
// 		for (int j = left; j < right; ++j) {
// 			streamer << data->operator()(i,j) << endl;
// 		}
// 		streamer << "]" << endl;
// 	}

// 	delete this;
// }
// ostream& operator<<(ostream& streamer, const SubMatrix& sm) {
// 	sm.Print(streamer);
// 	return streamer;
// }

// // Print to an fstream
// // @param ofstream& fileOut - print to this ofstream
// void SubMatrix::Print(fstream& outFile) const {
// 	for (int i = top; i < down; ++i) {
// 		outFile << "\t\t[ ";
// 		for (int j = left; j < right; ++j) {
// 			outFile << data->operator()(i,j) << endl;
// 		}
// 		outFile << "]" << endl;
// 	}

// 	delete this;
// }
// ofstream& operator<<(ofstream& outFile, const SubMatrix& sm) {
// 	sm.Print(outFile);
// 	return outFile;
// }



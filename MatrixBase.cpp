
#include "MatrixBase.h"


double& MatrixBase::operator()(int r, int c) {
	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
		throw "ERROR:  "
			  "double& MatrixBase::operator()(int, int)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	return (*data_ptr)[r+top][c+left];
}

const double& MatrixBase::operator()(int r, int c) const {
	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
		throw "ERROR:  "
			  "double& MatrixBase::operator()(int, int)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	return (*data_ptr)[r+top][c+left];
}

// Set the entire Matrix equal to the input value
// @param double value - the value to insert
void MatrixBase::operator=(double value) {
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			(*data_ptr)[i+top][j+left] = value;
		}
	}
}



// Print to an ostream
// @param ostream& streamer - print to this ostream
void MatrixBase::Print(ostream& streamer) const {
	// streamer << endl << name << endl;
	streamer << "\tRows: " << nRows << endl;
	streamer << "\tCols: " << nCols << endl;
	for (vector<vector<double>>::const_iterator
		 i = data_ptr->begin(); i != data_ptr->end(); ++i) {
		streamer << "\t\t[ ";
		for (vector<double>::const_iterator
			 j = i->begin(); j != i->end(); ++j) {
			streamer << *j << " ";
		}
		streamer << "]" << endl;
	}
}
ostream& operator<<(ostream& streamer, const MatrixBase& mat) {
	mat.Print(streamer);
	return streamer;
}

// Print to an fstream
// @param ofstream& fileOut - print to this ofstream
void MatrixBase::Print(ofstream& fileOut) const {
	// fileOut << endl << name << endl;
	fileOut << "\tRows: " << nRows << endl;
	fileOut << "\tCols: " << nCols << endl;
	for (vector<vector<double>>::const_iterator
		 i = data_ptr->begin(); i != data_ptr->end(); ++i) {
		fileOut << "\t\t[ ";
		for (vector<double>::const_iterator
			 j = i->begin(); j != i->end(); ++j) {
			fileOut << *j << " ";
		}
		fileOut << "]" << endl;
	}
}
ofstream& operator<<(ofstream& fileOut, const MatrixBase& mat) {
	mat.Print(fileOut);
	return fileOut;
}





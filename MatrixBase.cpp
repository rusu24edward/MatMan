
#include "MatrixBase.h"


double& MatrixBase::operator()(int r_, int c_) {
	if (r_ >= nRows || c_ >= nCols || r_ < 0 || c_ < 0) {
		throw "ERROR:  "
			  "double& MatrixBase::operator()(int, int)\n"
			  "\tAttempting to access elements outside the matrix range.";
	}
	int r = r_ + top;
	int c = c_ + left;
	return (*data_ptr)[r][c];
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





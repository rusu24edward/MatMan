

#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <vector>
#include <fstream>
// #include <utility>

#include "Matrix.h"

class Matrix;

using namespace std;

class SubMatrix {
	friend class Matrix;

public:

	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //

	// Set the values pointed to by the LHS to the values from the RHS
	// @param const SubMatrix& sm - RHS SubMatrix from which to copy
	// void operator=(const SubMatrix& sm) {
	// 	if (nRows != sm.nRows || nCols != sm.nCols) {
	// 		throw "ERROR:  "
	// 			  "SubMatrix& SubMatrix::operator=(const SubMatrix&)\n"
	// 			  "\tMatrix subsets are not the same size.";
	// 	}
	// 	vector<pair<vd_iter, vd_iter>>::iterator left_i = limits.begin();
	// 	vector<pair<vdc_iter, vdc_iter>>::const_iterator right_i = sm.limits.begin();
	// 	while (left_i != limits.end() && right_i != sm.limits.end()) {

	// 		vd_iter left_j = left_i->first;
	// 		vdc_iter right_j = right_i->first;
	// 		while (left_j != left_i->second & right_j != right_i->second) {
	// 			*left_j = *right_j;
	// 			left_j++;
	// 			right_j++;
	// 		}
	// 		left_i++;
	// 		right_i++;
	// 	}
	// }
		// GETTING LOTS OF ERRORS BECAUSE THE ARGUMENT IS CONSTANT, BUT
		// THE RHS ITERATORS ARE NOT. UPDATE THE ITERATROS
	// Set the values pointed to by the LHS to the values from the RHS
	// @param const Matrix& mat - RHS Matrix from which to copy
	// void operator=(const Matrix& mat) {
	// 	if (nRows != mat.nRows || nCols != mat.nCols) {
	// 		throw "ERROR:  "
	// 			  "SubMatrix& SubMatrix::operator=(const Matrix&)\n"
	// 			  "\tLHS SubMatrix is not the same size as the RHS Matrix.";
	// 	}
	// 	int r = 0;
	// 	int c = 0;
	// 	for (vector<pair<vd_iter, vd_iter>>::iterator
	// 			i = limits.begin(); i != limits.end(); ++i) {
	// 		for (vd_iter j = i->first; j != i->second; ++j) {
	// 			*j = mat.extract(r, c);
	// 			c++;
	// 		}
	// 		r++;
	// 	}
	// }



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	// Print to an ostream
	// @param ostream& streamer - print to this ostream
	void Print(ostream& fileOut) const {
		fileOut << endl << "SubMatrix" << endl;
		for (vector<pair<vd_iter, vd_iter>>::const_iterator
				i = limits.begin(); i != limits.end(); ++i) {
			fileOut << "\t\t[ ";
			for (vd_iter j = i->first; j != i->second; ++j) {
				fileOut << *j << " ";
			}
			fileOut << "]" << endl;
		}
	}
	friend ostream& operator<<(ostream& fileOut, const SubMatrix& sm) {
		sm.Print(fileOut);
		return fileOut;
	}

	// Print to an ofstream
	// @param ofstream& streamer - print to this ofstream
	void Print(ofstream& fileOut) const {
		fileOut << endl << "SubMatrix" << endl;
		for (vector<pair<vd_iter, vd_iter>>::const_iterator
				i = limits.begin(); i != limits.end(); ++i) {
			fileOut << "\t\t[ ";
			for (vd_iter j = i->first; j != i->second; ++j) {
				fileOut << *j << " ";
			}
			fileOut << "]" << endl;
		}
	}
	friend ofstream& operator<<(ofstream& fileOut, const SubMatrix& sm) {
		sm.Print(fileOut);
		return fileOut;
	}

private:
	typedef vector<double>::iterator vd_iter;
	typedef vector<double>::const_iterator vdc_iter;
	vector<pair<vd_iter, vd_iter>> limits;
	int nRows, nCols;
};

#endif

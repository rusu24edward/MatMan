

#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <vector>
#include <fstream>
// #include <utility>

using namespace std;

class SubMatrix {
	friend class Matrix;

public:


	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	// Print to an ostream
	// @param ostream& streamer - print to this ostream
	void Print(ostream& fileOut) const {
		fileOut << endl << "SubMatrix" << endl;
		for (vector<pair<vdc_iter, vdc_iter>>::const_iterator
				i = limits.begin(); i != limits.end(); ++i) {
			fileOut << "\t\t[ ";
			for (vdc_iter j = i->first; j != i->second; ++j) {
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
		for (vector<pair<vdc_iter, vdc_iter>>::const_iterator
				i = limits.begin(); i != limits.end(); ++i) {
			fileOut << "\t\t[ ";
			for (vdc_iter j = i->first; j != i->second; ++j) {
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
	typedef vector<double>::const_iterator vdc_iter;
	vector<pair<vdc_iter, vdc_iter>> limits;
};

#endif

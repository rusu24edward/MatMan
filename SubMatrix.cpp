
#include "SubMatrix.h"

using namespace std;


// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void SubMatrix::Print(ostream& fileOut) const {
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
ostream& operator<<(ostream& fileOut, const SubMatrix& sm) {
	sm.Print(fileOut);
	return fileOut;
}

// Print to an ofstream
// @param ofstream& streamer - print to this ofstream
void SubMatrix::Print(ofstream& fileOut) const {
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
ofstream& operator<<(ofstream& fileOut, const SubMatrix& sm) {
	sm.Print(fileOut);
	return fileOut;
}

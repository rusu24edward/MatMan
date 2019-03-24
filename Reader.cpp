
#include "Reader.h"

#include <vector>

Matrix Reader::Read(const string& fileName) {

	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		throw "ERROR:  "
			  "Matrix Reader::Read(const string&)\n"
			  "\tCannot open " << fileName << "!" << endl;
		cout << "FAILURE"
	}

	vector<vector<double>> dataIn;
	// Loop over all lines in the inFile with getline
	// In each line, loop over all strings with stringstreamer
	// rowIn.push_back(convert2Double(string));

	inFile.close();

	return Matrix(dataIn);
}

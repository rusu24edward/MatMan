
#include "Reader.h"

#include <vector>
#include <sstream>

// Read a comma delimitted file into a Matrix
// @param const string& fileName - the name of the file
// @return Matrix - the resulting Matrix
Matrix Reader::Read(const string& fileName) {

	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		throw "ERROR:  "
			  "Matrix Reader::Read(const string&)\n"
			  "\tCannot open file!";
	}

	vector<vector<double>> dataIn;
	string line;
	while (getline(inFile, line)) { // Loop over each line
		istringstream iss(line);
		vector<double> rowIn;
		double inputDouble;
		while(iss >> inputDouble) { // Loop over each item in the line
			rowIn.push_back(inputDouble);
	        if (iss.peek() == ',') {
	            iss.ignore();
	        }
		}
		dataIn.push_back(rowIn);
	}

	inFile.close();

	return Matrix(dataIn);
}

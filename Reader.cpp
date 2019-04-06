
#include "Reader.h"

#include <vector>
#include <sstream>
#include <string>

// Read a file into a Matrix.
// @param const string& fileName - the name of the file
// @param const char* delimiter - single character that separates columns
// @return Matrix - the resulting Matrix
Matrix Reader::Read(const string& fileName, char delimiter) {

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
			std::cout << inputDouble << std::endl;
			rowIn.push_back(inputDouble);
	        if (iss.peek() == delimiter) {
	            iss.ignore();
	        }
		}
		dataIn.push_back(rowIn);
	}

	inFile.close();

	return Matrix(dataIn);
}

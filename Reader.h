
#ifndef READER_H
#define READER_H

#include <string>

#include "Matrix.h"

using namespace std;

// Reader class provides the utilities needed to read files into various data storage classes.
// Current support:
//		- Read a file into a Matrix. Each line in the file is a row in the Matrix and the columns
//			are delimited by the user-specified character.
class Reader {

public:

	// --- Functions --- //
	static Matrix Read(const string&, char);

};

#endif

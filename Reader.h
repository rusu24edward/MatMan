
#ifndef READER_H
#define READER_H

#include <string>

#include "Matrix.h"

using namespace std;

// Reader class provides the utilities needed to read files into various data storage classes.
// Current support:
//		- Read a comma-delimitted file into a Matrix
class Reader {

public:

	// --- Functions --- //
	static Matrix Read(const string&);

};

#endif

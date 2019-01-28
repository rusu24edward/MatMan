
#include "SubVector.h"

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Default constructor sets the pointers to 0
SubVector::SubVector() {
	data = limit = 0;
}

// Alternate constructor sets the pointers to the input
// @param double* d - the beginning pointer
// @param double* l - the end pointer
SubVector::SubVector(double* d, double* l) {
	data = d;
	limit = l;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets the pointers to 0
SubVector::~SubVector() {
	data = limit = 0;
}



// ------------------------------- //
// --- Functions and Operators --- //
// ------------------------------- //

// Set the values to the values from the input Vector
// @param const Vector& vec - the input vector from which to copy
void SubVector::operator=(const Vector& vec) {
	if ((vec.limit - vec.data) != (limit - data)) {
		throw "ERROR:  "
			  "void SubVector::operator=(const Vector& vec)\n"
			  "\tVectors are not the same size.";
	}

	double* leftIter = data;
	double* leftEnd = limit;
	const double* rightIter = vec.data;
	const double* rightEnd = vec.limit;
	while (leftIter != leftEnd && rightIter != rightEnd) {
		*leftIter = *rightIter;
		leftIter++;
		rightIter++;
	}

	delete this;
}

// Set the values to the values from the input SubVector
// @param - const SubVector& sv - the input SubVector from which to copy
void SubVector::operator=(SubVector& sv) {
	if ((sv.limit - sv.data) != (limit - data)) {
		throw "ERROR:  "
			  "void SubVector::operator=(const SubVector& sv)\n"
			  "\tVectors are not the same size.";
	}

	double* leftIter = data;
	double* leftEnd = limit;
	const double* rightIter = sv.data;
	const double* rightEnd = sv.limit;
	while (leftIter != leftEnd && rightIter != rightEnd) {
		*leftIter = *rightIter;
		leftIter++;
		rightIter++;
	}

	delete &sv;
	delete this;
}

// Set the values to the specified double
// @param double d - Set values to this double
void SubVector::operator=(double d) {
	for (double* i = data; i != limit; ++i) {
		*i = d;
	}
	delete this;
}



// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void SubVector::Print(ostream& streamer) const {
	streamer << "\t\t[ ";
	for (const double* i = data; i != limit; ++i) {
		streamer << *i << " ";
	}
	streamer << "]" << endl;

	delete this;
}
ostream& operator<<(ostream& streamer, const SubVector& sv) {
	sv.Print(streamer);
	return streamer;
}

// Print to an fstream
// @param ofstream& fileOut - print to this ofstream
void SubVector::Print(fstream& outFile) const {
	outFile << "\t\t[ ";
	for (const double* i = data; i != limit; ++i) {
		outFile << *i << " ";
	}
	outFile << "]" << endl;

	delete this;
}
ofstream& operator<<(ofstream& outFile, const SubVector& sv) {
	sv.Print(outFile);
	return outFile;
}



#include "SubVector.h"

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Constructor sets the pointers to the input
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
	if ((vec.end() - vec.begin()) != (limit - data)) {
		throw "ERROR:  "
			  "void SubVector::operator=(const Vector&)\n"
			  "\tVectors are not the same size.";
	}

	double* leftIter = data;
	double* leftEnd = limit;
	const double* rightIter = vec.begin();
	const double* rightEnd = vec.end();
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
			  "void SubVector::operator=(const SubVector&)\n"
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
	for (double* ptr = data; ptr != limit; ++ptr) {
		*ptr = d;
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
	for (const double* ptr = data; ptr != limit; ++ptr) {
		streamer << *ptr << " ";
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
	for (const double* ptr = data; ptr != limit; ++ptr) {
		outFile << *ptr << " ";
	}
	outFile << "]" << endl;

	delete this;
}
ofstream& operator<<(ofstream& outFile, const SubVector& sv) {
	sv.Print(outFile);
	return outFile;
}


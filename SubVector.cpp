
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
// @param const MyVector& vec - the input vector from which to copy
void SubVector::operator=(const MyVector& vec) {
	// TODO: Check that they are indeed the same size
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
	// TODO: Check that they are indeed the same size
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

void Print(ostream&) const;
friend ostream& operator<<(ostream&, const SubVector&);
void Print(fstream&) const;
friend ofstream& operator<<(ofstream7, const SubVector&);


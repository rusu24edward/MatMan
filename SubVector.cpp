
#include "SubVector.h"

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Constructor sets the data and the limits
// @param Vector* vec - pointer to the Vector data
// @param int first - first index
// @param int last - last index
SubVector::SubVector(Vector* vec, int first, int last) {
	data = vec;
	begin = first;
	end = last + 1;
	length = end - begin;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all to 0
SubVector::~SubVector() {
	data = 0;
	begin = end = 0;
}



// ------------------------------- //
// --- Functions and Operators --- //
// ------------------------------- //

// Set the values to the values from the input Vector
// @param const Vector& vec - the input Vector from which to copy
void SubVector::operator=(const Vector& vec) {
	if (length != vec.size()) {
		throw "ERROR:  "
			  "void SubVector::operator=(const Vector&)\n"
			  "\tVectors are not the same size.";
	}

	for (int i = 0; i < length; ++i) {
		data->operator()(i+begin) = vec(i);
	}

	delete this;
}

// Set the values to the values from the input SubVector
// @param - const SubVector& sv - the input SubVector from which to copy
void SubVector::operator=(SubVector& sv) {
	if (length != sv.length) {
		throw "ERROR:  "
			  "void SubVector::operator=(SubVector&)\n"
			  "\tVectors are not the same size.";
	}

	for (int i = 0; i < length; ++i) {
		data->operator()(i+begin) = sv.data->operator()(i+sv.begin);
	}

	delete &sv;
	delete this;
}

// Set the values to the specified double
// @param double d - Set values to this double
void SubVector::operator=(double d) {
	for (int i = 0; i < length; ++i) {
		data->operator()(i+begin) = d;
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
	for (int i = begin; i < end; ++i) {
		streamer << data->operator()(i) << " ";
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
	for (int i = begin; i < end; ++i) {
		outFile << data->operator()(i) << " ";
	}
	outFile << "]" << endl;

	delete this;
}
ofstream& operator<<(ofstream& outFile, const SubVector& sv) {
	sv.Print(outFile);
	return outFile;
}


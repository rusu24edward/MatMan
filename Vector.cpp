
#include "Vector.h"

#include <algorithm>

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Default constructor sets the fields to their default states
Vector::Vector() {
	setFields();
	name = UNAMED;
}

// Alternate constructor sets the number of elements and creates an appropriately
// sized vector.
// @param int n - the number of elements
Vector::Vector(int n) {
	setFields(n);
	name = UNAMED;
}

// Alternate constructor sets the number of elements and fills an appropriately
// sized vector with the specified value. If value not specified, then default
// to 0.
// @param int n - the number of elements
// @param double value - set each element in the vector to this value
Vector::Vector(int n, double value) {
	setFields(n, value);
	name = UNAMED;
}

// Alternate constructor converts the input vector of doubles to a Vector.
// @param const vector<double>& d - copy the values out of this vector
Vector::Vector(const vector<double>& d) {
	setFields(d);
	name = UNAMED;
}

// Copy constructor copies the input Vector.
// @param const Vector& vec - Vector from which to copy
Vector::Vector(const Vector& vec) {
	setFields(vec);
	name = UNAMED;
}

// Copy constructor copies the input SubVector and then deletes it
// @param SubVector& sv - the SubVector from which to copy
Vector::Vector(SubVector& sv) {
	setFields(sv);
	name = UNAMED;
	delete &sv;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all fields to their default states and removes the name
Vector::~Vector() {
	deleteFields();
	name = "";
}



// ---------------------------- //
// --- Assignment Operators --- //
// ---------------------------- //

// Assignment operator blows out the Vector and replace it with the input vector.
// @param const vector<double>& d - copy the data
// @return Vector& - this Vector
Vector& Vector::operator=(const vector<double>& d) {
	deleteFields();
	setFields(d);
	return *this;
}

// Assignemnt operator blows out the Vector data and sets it to the RHS. If the
// RHS is the same object, then just return this.
// @param const Vector& vec - Vector to copy
// @return Vector& - this Vector
Vector& Vector::operator=(const Vector& vec) {
	if (this != &vec) {
		deleteFields();
		setFields(vec);
	}
	return *this;
}

// Assignment operator blows out the Vector data and sets it to the specified
// SubVector. If the RHS holds the Vector data that is the same as this, then
// just return this.
// @param SubVector& sv - SubVector to copy
// @return - this Vector
Vector& Vector::operator=(SubVector& sv) {
	if (this != sv.data) {
		deleteFields();
		setFields(sv);
	}
	delete &sv;
	return *this;
}



// ---------------------------- //
// --- Accessors & Mutators --- //
// ---------------------------- //

// Get the length of the Vector
// @return int - the length of the Vector
int Vector::getLength() const {
	return length;
}

// Get the name
// @return const string& - the name of the Vector
const string& Vector::getName() const {
	return name;
}
// Set the name
// @param const string& n - the name of the vector
void Vector::setName(const string& n) {
	name = n;
}


// ------------------------------- //
// --- Functions and Operators --- //
// ------------------------------- //

// --- Element support --- //

// Extract the value at the specified index
// @param int n - the element index
// @return double& - the value at this index
double& Vector::operator()(int n) {
	if (n >= length || n < 0) {
		throw "ERROR:  "
			  "double& Vector::operator()(int)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return data[n];
}

// Set the entire vector equal to the input value
// @param double value - the input value
void Vector::operator=(double value) {
	for (std::vector<double>::iterator ptr = data.begin();
		 ptr != data.end(); ++ptr) {
		*ptr = value;
	}
}


// --- SubVector support --- //

// Generate a SubVector from this Vector using the indicies
// @param int first - the beginning of the SubVector
// @paran int last - the end of the SubVector
// @return SubVector& - the SubVector
SubVector& Vector::operator()(int first, int last) {
	if (last < first) {
		throw "ERROR:  "
			  "SubVector& Vector::operator()(int, int)\n"
			  "\tUnordered Range.";
	}
	if (first < 0 || last >= length) {
		throw "ERROR:  "
			  "SubVector& Vector::operator()(int, int)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return *(new SubVector(this, first, last));
}



// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void Vector::Print(ostream& streamer) const {
	streamer << endl << name << endl;
	streamer << "\tElements: " << length << endl;
	streamer << "\t\t[ ";
	for (std::vector<double>::const_iterator ptr = data.begin();
		 ptr != data.end(); ++ptr) {
		streamer << *ptr << " ";
	}
	streamer << "]" << endl;
}
ostream& operator<<(ostream& streamer, const Vector& vec) {
	vec.Print(streamer);
	return streamer;
}

// Print to an fstream
// @param ofstream& fileOut - print to this ofstream
void Vector::Print(ofstream& fileOut) const {
	fileOut << endl << name << endl;
	fileOut << "\tElements: " << length << endl;
	fileOut << "\t\t[ ";
	for (std::vector<double>::const_iterator ptr = data.begin();
		 ptr != data.end(); ++ptr) {
		fileOut << *ptr << " ";
	}
	fileOut << "]" << endl;
}
ofstream& operator<<(ofstream& fileOut, const Vector& vec) {
	vec.Print(fileOut);
	return fileOut;
}



// ------------------------ //
// --- Helper Functions --- //
// ------------------------ //

// --- Object Construction Helpers --- //

// Set the class fields
// @param int n - the number of elements. Default is 0
// @param double value - set each element in the Vector to this value.
// Default is 0.
void Vector::setFields(int n, double value) {
	data = vector<double>(n, value);
	length = n;
}

// Set the class fields
// @param const vector<double>& d - vector from which to copy
void Vector::setFields(const vector<double>& d) {
	data = d;
	length = data.size();
}

// Set the class fields
// @param const Vector& vec - Vector from which to copy
void Vector::setFields(const Vector& vec) {
	data = vec.data;
	length = data.size();
}

// Set the class fields
// @param const SubVector& sv - SubVector from which to copy
void Vector::setFields(const SubVector& sv) {
	length = sv.length;
	copy(sv.data->data.begin() + sv.begin, sv.data->data.begin() + sv.end, back_inserter(data));
}

// Delete the class fields
void Vector::deleteFields() {
	data.clear();
	length = 0;
}


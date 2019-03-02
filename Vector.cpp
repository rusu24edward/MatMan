
#include "Vector.h"

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
// SubVector. If the RHS points to the same beginning and end, then just return
// this.
// @param SubVector& sv - SubVector to copy
// @return - this Vector
Vector& Vector::operator=(SubVector& sv) {
	if (data != sv.data || limit != sv.limit) {
		deleteFields();
		setFields(sv);
	}
	delete &sv;
	return *this;
}



// ---------------------------- //
// --- Accessors & Mutators --- //
// ---------------------------- //

// Get a constant pointer to the beginning of the vector
// @return const double* - the pointer
const double* Vector::begin() const {
	return data;
}
// Get a constant pointer to one past the end of the vector
// @return const double* - the pointer
const double* Vector::end() const {
	return limit;
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
	if (n >= (limit - data) || n < 0) {
		throw "ERROR:  "
			  "double& Vector::operator()(int)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return *(data + n);
}

// Set the entire vector equal to the input value
// @param double value - the input value
void Vector::operator=(double value) {
	for (double* ptr = data; ptr != limit; ++ptr) {
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
	if (first < 0 || last >= (limit - data)) {
		throw "ERROR:  "
			  "SubVector& Vector::operator()(int, int)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return *(new SubVector(data + first, data + last + 1));
}



// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void Vector::Print(ostream& streamer) const {
	streamer << endl << name << endl;
	streamer << "\tElements: " << limit - data << endl;
	streamer << "\t\t[ ";
	for (const double* ptr = data; ptr != limit; ++ptr) {
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
	fileOut << "\tElements: " << limit - data << endl;
	fileOut << "\t\t[ ";
	for (const double* ptr = data; ptr != limit; ++ptr) {
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
	data = new double[n];
	limit = data + n;
	for (double* ptr = data; ptr != limit; ++ptr) {
		*ptr = value;
	}
}

// Set the class fields
// @param const vector<double>& d - vector from which to copy
void Vector::setFields(const vector<double>& d) {
	int n = d.size();
	data = new double[n];
	limit = data + n;

	int i = 0;
	for (double* ptr = data; ptr != limit; ++ptr) {
		*ptr = d[i++];
	}
}

// Set the class fields
// @param const Vector& vec - Vector from which to copy
void Vector::setFields(const Vector& vec) {
	int n = vec.limit - vec.data;
	data = new double[n];
	limit = data + n;

	double* ptr1;
	const double* ptr2;
	for (ptr1 = data, ptr2 = vec.begin();
		 ptr1 != limit && ptr2 != vec.limit;
		 ++ptr1, ++ptr2) {
		*ptr1 = *ptr2;
	}
}

// Set the class fields
// @param const SubVector& sv - SubVector from which to copy
void Vector::setFields(const SubVector& sv) {
	int n = sv.limit - sv.data;
	data = new double[n];
	limit = data + n;

	double* ptr1;
	const double* ptr2;
	for (ptr1 = data, ptr2 = sv.data;
		 ptr1 != limit, ptr2 != sv.limit;
		 ptr1++, ptr2++) {
		*ptr1 = *ptr2;
	}
}

// Delete the class fields
void Vector::deleteFields() {
	delete [] data;
	data = limit = 0;
}


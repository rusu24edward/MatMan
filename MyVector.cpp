
#include "MyVector.h"

using namespace std;

// -------------------- //
// --- Constructors --- //
// -------------------- //

// Default constructor sets the fields to their default states
MyVector::MyVector() {
	setFields();
	name = UNAMED;
}

// Alternate constructor sets the number of elements and creates an appropriately
// sized vector.
// @param int n - the number of elements
MyVector::MyVector(int n) {
	setFields(n);
	name = UNAMED;
}

// Alternate constructor sets the number of elements and fills an appropriately
// sized vector with the specified value. If value not specified, then default
// to 0.
// @param int n - the number of elements
// @param double value - set each element in the vector to this value
MyVector::MyVector(int n, double value) {
	setFields(n, value);
	name = UNAMED;
}

// Alternate constructor converts the input vectors of doubles to a MyVector.
// @param const vector<double> d - copy the values out of this vector
MyVector::MyVector(const vector<double>& d) {
	setFields(d);
	name = UNAMED;
}

// Copy constructor copies the input MyVector.
// @param const MyVector& vec - MyVector from which to copy
MyVector::MyVector(const MyVector& vec) {
	setFields(vec);
	name = UNAMED;
}

// Copy constructor copies the input SubVector and then deletes it
// @param SubVector& sv - the SubVector from which to copy
MyVector::MyVector(SubVector& sv) {
	setFields(sv);
	name = UNAMED;
	delete &sv;
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all fields to their default states and removes the name
MyVector::~MyVector() {
	deleteFields();
}



// ---------------------------- //
// --- Assignment Operators --- //
// ---------------------------- //

// Assignment operator blows out the MyVector and replace it with the input vector.
// @param const vector<double>& d - copy the data
// @return MyVector& - this MyVector
MyVector& MyVector::operator=(const vector<double>& d) {
	deleteFields();
	setFields(d);
	return *this;
}

// Assignemnt operator blows out the MyVector data and sets it to the RHS. If the
// RHS is the same object, then just return this.
// @param const MyVector& vec - MyVector to copy
// @return MyVector& - this MyVector
MyVector& MyVector::operator=(const MyVector& vec) {
	if (this != &vec) {
		deleteFields();
		setFields(vec);
	}
	return *this;
}

// Assignment operator blows out the MyVector data and sets it to the specified
// SubVector. If the RHS points to the same beginning and end, then just return
// this.
// @param SubVector& sv - SubVector to copy
// @return - this MyVector
MyVector& MyVector::operator=(SubVector& sv) {
	if (data != sv.data && limit != sv.limit) {
		deleteFields();
		setFields(sv);
	}
	delete &sv;
	return *this;
}



// ---------------------------- //
// --- Accessors & Mutators --- //
// ---------------------------- //

// --- Name Access and Mutation --- //

// Get the name of the MyVector
// @return const string& - the MyVector's name
const string& MyVector::getName() const {
	return name;
}

// Set the name of the MyVector
// @param const string& n - the MyVector's name
void MyVector::setName(const string& n) {
	name = n;
}



// ------------------------------- //
// --- Functions and Operators --- //
// ------------------------------- //

// --- Element insertion and extraction --- //

// Extract the value at the specified index
// @param int n - the element index
// @return const double - the value at this index
const double& MyVector::extract(int n) const {
	if (n >= nElements || n < 0) {
		throw "ERROR:  "
			  "const double MyVector::extract(int) const\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return data[n];
}
const double& MyVector::operator()(int n) const {
	if (n >= nElements || n < 0) {
		throw "ERROR:  "
			  "const double MyVector::operator()(int) const\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return data[n];
}
double& MyVector::operator()(int n) {
	if (n >= nElements || n < 0) {
		throw "ERROR:  "
			  "double MyVector::operator()(int)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return data[n];
}

// Insert specified value at specified index
// @param int n - the row index
// @param double value - the value to insert at the index
void MyVector::insert(int i, double value) {
	if (i >= nElements || i < 0) {
		throw "ERROR:  "
			  "void MyVector::insert(int, double)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	data[i] = value;
}

// Insert a value to all elements of the MyVector
// @param double value - the value to insert
void MyVector::insert(double value) {
	for (int i = 0; i < nElements; ++i) {
		data[i] = value;
	}
}
void MyVector::operator=(double value) {
	for (int i = 0; i < nElements; ++i) {
		data[i] = value;
	}
}


// --- SubVector support --- //

SubVector& MyVector::operator()(int beginning, int end) {
	if (end < beginning) {
		throw "ERROR:  "
			  "SubVector& MyVector::operator()(int, int)\n"
			  "\tUnordered Range.";
	}
	if (beginning < 0 || end >= nElements) {
		throw "ERROR:  "
			  "SubVector& MyVector::operator()(int, int)\n"
			  "\tAttempting to access elements outside the Vector range.";
	}
	return *(new SubVector(data + beginning, data + end+1));
}



// ---------------- //
// --- Printing --- //
// ---------------- //

// Print to an ostream
// @param ostream& streamer - print to this ostream
void MyVector::Print(ostream& streamer) const {
	streamer << endl << name << endl;
	streamer << "\tElements: " << nElements << endl;
	streamer << "\t\t[ ";
	for (int i = 0; i < nElements; ++i) {
		streamer << data[i] << " ";
	}
	streamer << "]" << endl;
}
ostream& operator<<(ostream& streamer, const MyVector& vec) {
	vec.Print(streamer);
	return streamer;
}

// Print to an fstream
// @param ofstream& fileOut - print to this ofstream
void MyVector::Print(ofstream& fileOut) const {
	fileOut << endl << name << endl;
	fileOut << "\tElements: " << nElements << endl;
	fileOut << "\t\t[ ";
	for (int i = 0; i < nElements; ++i) {
		fileOut << data[i] << " ";
	}
	fileOut << "]" << endl;
}
ofstream& operator<<(ofstream& fileOut, const MyVector& vec) {
	vec.Print(fileOut);
	return fileOut;
}



// ------------------------ //
// --- Helper Functions --- //
// ------------------------ //

// --- Object Construction Helpers --- //

// Set the class fields
// @param int n - the number of elements. Default is 0
// @param double value - set each element in the MyVector to this value.
// Default is 0.
void MyVector::setFields(int n, double value) {
	nElements = n;
	data = new double[n];
	limit = data + nElements;
	for (int i = 0; i < nElements; ++i) {
		data[i] = value;
	}
}

// Set the class fields
// @param const vector<double>& d - vector from which to copy
void MyVector::setFields(const vector<double>& d) {
	nElements = d.size();
	data = new double[nElements];
	limit = data + nElements;
	for (int i = 0; i < nElements; ++i) {
		data[i] = d[i];
	}
}

// Set the class fields
// @param const MyVector& vec - Vector from which to copy
void MyVector::setFields(const MyVector& vec) {
	nElements = vec.nElements;
	data = new double[nElements];
	limit = data + nElements;
	for (int i = 0; i < nElements; ++i) {
		data[i] = vec.data[i];
	}
}

// Set the class fields
// @param const SubVector sv - SubVector from which to copy
void MyVector::setFields(const SubVector& sv) {
	nElements = sv.limit - sv.data;
	data = new double[nElements];
	limit = data + nElements;

	for (int i = 0; i < nElements; ++i) {
		data[i] = *(sv.data + i);
	}
}

// Delete the class fields
void MyVector::deleteFields() {
	nElements = 0;
	delete [] data;
	data = limit = 0;
}


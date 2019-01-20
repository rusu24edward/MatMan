
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
	// TODO: More here
}

// Copy constructor copies the input MyVector.
// @param const MyVector& vec - MyVector from which to copy
MyVector::MyVector(const MyVector& vec) {
	setFields(vec);
	name = UNAMED;
	// TODO: More here
}



// ------------------ //
// --- Destructor --- //
// ------------------ //

// Destructor sets all fields to their default states and removes the name
MyVector::~MyVector() {
	nElements = 0;
	delete [] data;
	data = limit = 0;
}



// ---------------------------- //
// --- Assignment Operators --- //
// ---------------------------- //

// Assignemnt operator blows out the MyVector data and sets it to the RHS
// @param const MyVector& vec - MyVector to copy
// @return MyVector& - this MyVector
MyVector& MyVector::operator=(const MyVector& vec) {
	if (this != &vec) {
		setFields(vec);
		// TODO: more here
	}
	return *this;
}

// Assignment operator blows out the MyVector and replace it with the input vector
// @param const vector<double>& d - copy the data
// @return MyVector& - this MyVector
MyVector& MyVector::operator=(const vector<double>& d) {
	setFields(d);
	// TODO: more here

	return *this;
}



// ---------------------------- //
// --- Accessors & Mutators --- //
// ---------------------------- //

// -- MyVector Name --- //

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

// // --- Element insertion and extraction --- //

// // Extract the value at the specified index
// // @param int r - the row index
// // @param int c - the column index
// // @return const double - the value at this index
// const double MyVector::extract(int r, int c) const {
// 	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
// 		throw "ERROR:  "
// 			  "const double MyVector::extract(int, int) const\n"
// 			  "\tAttempting to access elements outside the MyVector range.";
// 	}
// 	return data[r][c];
// }
// const double MyVector::operator()(int r, int c) const {
// 	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
// 		throw "ERROR:  "
// 			  "const double MyVector::operator()(int, int) const\n"
// 			  "\tAttempting to access elements outside the MyVector range.";
// 	}
// 	return data[r][c];
// }

// // Insert specified value at specified index
// // @param int r - the row index
// // @param int c - the column index
// // @param double value - the value to insert at the index
// void MyVector::insert(int r, int c, double value) {
// 	if (r >= nRows || c >= nCols || r < 0 || c < 0) {
// 		throw "ERROR:  "
// 			  "void MyVector::insert(int, int, double)\n"
// 			  "\tAttempting to access elements outside the MyVector range.";
// 	}
// 	data[r][c] = value;
// }

// // Insert a value to all elements of the MyVector
// // @param double value - the value to insert
// void MyVector::insert(double value) {
// 	for (int i = 0; i < nRows; ++i) {
// 		for (int j = 0; j < nCols; ++j) {
// 			data[i][j] = value;
// 		}
// 	}
// }
// void MyVector::operator=(double value) {
// 	for (int i = 0; i < nRows; ++i) {
// 		for (int j = 0; j < nCols; ++j) {
// 			data[i][j] = value;
// 		}
// 	}
// }


// // --- MyVector Stucture --- //

// // Query the size of the MyVector
// // @return vector<int> - a 2 element vector that is {nRows, nCols}
// vector<int> MyVector::size() {
// 	return vector<int>{nRows, nCols};
// }

// // Query the length of the specified dimension
// // @param int d - The desired dimension. 1 for rows, 2 for cols.
// // @return int - the length of the MyVector along the given dimension.
// int MyVector::size(int d) {
// 	if (d <= 0 || d > 2) {
// 		throw "ERROR:  "
// 			  "int MyVector::size(int)\n"
// 			  "\tN/A dimension. Dimension must be 1 for rows or 2 for cols.";
// 	} else if (d == 1) {
// 		return nRows;
// 	} else if (d == 2) {
// 		return nCols;
// 	}
// }

// // Query the length of the longer dimension
// // @return int - the lenght of the longer dimension.
// int MyVector::length() {
// 	return nCols > nRows ? nCols : nRows;
// }


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
void MyVector::setFields(const vector<double>& d) {
	nElements = d.size();
	data = new double[nElements];
	limit = data + nElements;
	for (int i = 0; i < nElements; ++i) {
		data[i] = d[i];
	}
}

void MyVector::setFields(const MyVector& vec) {
	nElements = vec.nElements;
	data = new double[nElements];
	limit = data + nElements;
	for (int i = 0; i < nElements; ++i) {
		data[i] = vec.data[i];
	}
}
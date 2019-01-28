
#ifndef SUBVECTOR_H
#define SUBVECTOR_H

#include <iostream>
#include <fstream>

#include "MyVector.h"
class MyVector;

using namespace std;

// SubVector class provides the capabilities to manipulate sections of a Vector.
// Current support:
//		- Can only be created and destroyed by friend class Vector
//		- Equals operator for Vectors, SubVectors, and doubles.
class SubVector {

friend class MyVector;

public:

	// ------------------------------- //
	// --- Functions and Operators --- //
	// ------------------------------- //

	void operator=(const MyVector&);
	void operator=(SubVector&);
	void operator=(double);



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const SubVector&);
	void Print(fstream&) const;
	friend ofstream& operator<<(ofstream7, const SubVector&);





private:

	// -------------------- //
	// --- Constructors --- //
	// -------------------- //

	SubVector();
	SubVector(double* d, double* l);
	SubVector& operator=(const SubVector&);



	// ------------------ //
	// --- Destructor --- //
	// ------------------ //

	~SubVector();



	// ----------------------- //
	// --- Underlying Data --- //
	// ----------------------- //

	double* data;
	double* limit;
};

#endif

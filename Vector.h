
#ifndef Vector_H
#define Vector_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "SubVector.h"
class SubVector;

using namespace std;

// Vector class provides data storage and manipulation like a mathematical
// vector. Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
//		- Generate Vectors from vector<double>
//		- Extract value from index
//		- Insert value at index
//		- Set all elements to a number
//		- Generate SubVectors
//		- Generate Vectors from SubVectors
class Vector {

friend class SubVector;

public:

	// -------------------- //
	// --- Constructors --- //
	// -------------------- //

	Vector();
	Vector(int);
	Vector(int, double);
	Vector(const vector<double>&);
	Vector(const Vector&);
	Vector(SubVector&);



	// ------------------ //
	// --- Destructor --- //
	// ------------------ //

	~Vector();



	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //

	Vector& operator=(const vector<double>&);
	Vector& operator=(const Vector&);
	Vector& operator=(SubVector&);



	// ---------------------------- //
	// --- Accessors & Mutators --- //
	// ---------------------------- //

	// --- Name Access and Mutation --- //
	const string& getName() const;
	void setName(const string&);



	// ------------------------------- //
	// --- Functions and Operators --- //
	// ------------------------------- //

	// --- Element insertion and extraction --- //
	const double& extract(int) const;
	const double& operator()(int) const;
	double& operator()(int);
	void insert(int, double);
	void insert(double);
	void operator=(double);

	// --- SubVector support --- //
	SubVector& operator()(int, int);



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const Vector&);
	void Print(ofstream&) const;
	friend ofstream& operator<<(ofstream&, const Vector&);





private:

	// ------------------------ //
	// --- Helper Functions --- //
	// ------------------------ //

	// --- Object Construction Helpers --- //
	void setFields(int n = 0, double value = 0);
	void setFields(const vector<double>&);
	void setFields(const Vector&);
	void setFields(const SubVector&);
	void deleteFields();



	// ----------------------- //
	// --- Underlying Data --- //
	// ----------------------- //

	string name;
	const string UNAMED = "UNAMED";

	int nElements;
	double* data;
	double* limit;
};

#endif


#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "SubVector.h"
class SubVector;

using namespace std;

// MyVector class provides data storage and manipulation like a mathematical
// vector. Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
//		- Generate Vectors from vector<double>
//		- Extract value from index
//		- Insert value at index
//		- Set all elements to a number
class MyVector {

friend class SubVector;

public:

	// -------------------- //
	// --- Constructors --- //
	// -------------------- //

	MyVector();
	MyVector(int);
	MyVector(int, double);
	MyVector(const vector<double>&);
	MyVector(const MyVector&);
	MyVector(SubVector&);



	// ------------------ //
	// --- Destructor --- //
	// ------------------ //

	~MyVector();



	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //

	MyVector& operator=(const vector<double>&);
	MyVector& operator=(const MyVector&);
	MyVector& operator=(SubVector&);



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
	friend ostream& operator<<(ostream&, const MyVector&);
	void Print(ofstream&) const;
	friend ofstream& operator<<(ofstream&, const MyVector&);





private:

	// ------------------------ //
	// --- Helper Functions --- //
	// ------------------------ //

	// --- Object Construction Helpers --- //
	void setFields(int n = 0, double value = 0);
	void setFields(const vector<double>&);
	void setFields(const MyVector&);
	void setFields(const SubVector&);



	// ----------------------- //
	// --- Underlying Data --- //
	// ----------------------- //

	string name;
	const string UNAMED = "UNAMED";

	int nElements;
	double* data;
	double* limit;

	SubVector* sv;
};

#endif

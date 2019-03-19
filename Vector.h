
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "NamedObject.h"
#include "SubVector.h"
class SubVector;

using namespace std;

// Vector class provides data storage and manipulation like a mathematical
// vector. Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
//		- Generate Vectors from vector<double>
//		- Extract value from index
//		- Set all elements to a number
//		- Generate SubVectors
//		- Generate Vectors from SubVectors
class Vector : public NamedObject {

public:

	// --- Constructors --- //
	Vector();
	Vector(int);
	Vector(int, double);
	Vector(const vector<double>&);
	Vector(const Vector&);
	Vector(SubVector&);

	// --- Destructor --- //
	~Vector();

	// --- Assignment Operators --- //
	Vector& operator=(const vector<double>&);
	Vector& operator=(const Vector&);
	Vector& operator=(SubVector&);

	// --- Accessors & Mutators --- //
	int getLength() const;
	const string& getName() const;
	void setName(const string&);

	// --- Functions and Operators --- //
	double& operator()(int);
	const double& operator()(int) const;
	void operator=(double);
	SubVector& operator()(int, int);
	int size() const;
	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const Vector&);
	void Print(ofstream&) const;
	friend ofstream& operator<<(ofstream&, const Vector&);


private:

	// --- Helper Functions --- //
	void setFields(int n = 0, double value = 0);
	void setFields(const vector<double>&);
	void setFields(const Vector&);
	void setFields(const SubVector&);
	void deleteFields();

	// --- Underlying Data --- //
	vector<double> data;
	int length;
};

#endif

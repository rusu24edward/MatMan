
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// MyVector class provides data storage and manipulation like a mathematical
// vector. Current support:
//		- Basic class functionality (copying, assigning, printing, etc.).
class MyVector {
public:

	// -------------------- //
	// --- Constructors --- //
	// -------------------- //

	MyVector();
	MyVector(int);
	MyVector(int, double);
	MyVector(const vector<double>&);
	MyVector(const MyVector&);



	// ------------------ //
	// --- Destructor --- //
	// ------------------ //

	~MyVector();



	// ---------------------------- //
	// --- Assignment Operators --- //
	// ---------------------------- //

	MyVector& operator=(const MyVector&);
	MyVector& operator=(const vector<double>&);



	// ---------------------------- //
	// --- Accessors & Mutators --- //
	// ---------------------------- //

	// -- MyVector Name --- //
	const string& getName() const;
	void setName(const string&);



	// ------------------------------- //
	// --- Functions and Operators --- //
	// ------------------------------- //

	// --- Element insertion and extraction --- //
	// const double extract(int, int) const;
	// const double operator()(int, int) const;
	// void insert(int, int, double);
	// void insert(double);
	// void operator=(double);

	// // --- SubMyVector Extraction --- //
	// SubMyVector extract(int, int, int, int) const;
	// SubMyVector operator()(int, int, int, int) const;

	// // --- MyVector Stucture --- //
	// vector<int> size();
	// int size(int);
	// int length();



	// ---------------- //
	// --- Printing --- //
	// ---------------- //

	// void Print(ostream&) const;
	// friend ostream& operator<<(ostream&, const MyVector&);
	// void Print(ofstream&) const;
	// friend ofstream& operator<<(ofstream&, const MyVector&);

	// // --- DEBUG FUNCTION --- //
	// void DEBUG_PrintFromLimits() const;





private:

	// ------------------------ //
	// --- Helper Functions --- //
	// ------------------------ //

	// --- Object Construction Helpers --- //
	void setFields(int n = 0, double value = 0);
	void setFields(const vector<double>&);
	void setFields(const MyVector&);



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


#ifndef SUBVECTOR_H
#define SUBVECTOR_H

#include "MyVector.h"
class MyVector;

using namespace std;

// SubVector class provides the capabilities to manipulate
class SubVector {
friend class MyVector;


public:

	// SubVector();
	// SubVector(double* d, double* l);
	// SubVector& operator=(const SubVector&);

	void operator=(const MyVector&);
	void operator=(SubVector&);
	void operator=(double);

	// Add a printing function that deletes this upon returning.


private:

	SubVector();
	SubVector(double* d, double* l);
	SubVector& operator=(const SubVector&);

	~SubVector();

	double* data;
	double* limit;
};

#endif


#ifndef SUBVECTOR_H
#define SUBVECTOR_H

#include "MyVector.h"
class MyVector;

using namespace std;

class SubVector {

friend class MyVector;

public:

	SubVector();
	SubVector(double* d, double* l);
	SubVector& operator=(const SubVector&);

	void operator=(const MyVector&);
	void operator=(SubVector&);
	void operator=(double);

	// Add a printing function that deletes this upon returning.

	~SubVector();

private:

	double* data;
	double* limit;
};

#endif


#ifndef SUBVECTOR_H
#define SUBVECTOR_H

using namespace std;

class SubVector {
public:

	SubVector();
	SubVector(double* d, double* l);
	// Set data to d and limit to l
	SubVector& operator=(const SubVector&);
	// Set data to d and limit to l

	~SubVector();

	// Functions I want to support
	// = Vector
	// = SubVector
private:

	double* data;
	double* limit;
};

#endif

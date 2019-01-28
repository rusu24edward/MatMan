
#include "SubVector.h"

#include <iostream>

using namespace std;

SubVector::SubVector() {
	data = limit = 0;
}

SubVector::SubVector(double* d, double* l) {
	data = d;
	limit = l;
}

SubVector::~SubVector() {
	data = limit = 0;
}

void SubVector::operator=(const MyVector& vec) {
	// Run a test that they are indeed the same size
	double* leftIter = data;
	double* leftEnd = limit;
	const double* rightIter = vec.data;
	const double* rightEnd = vec.limit;
	while (leftIter != leftEnd && rightIter != rightEnd) {
		*leftIter = *rightIter;
		leftIter++;
		rightIter++;
	}

	delete this;
}

void SubVector::operator=(SubVector& sv) {
	// Run a test that they are indeed the same size
	double* leftIter = data;
	double* leftEnd = limit;
	const double* rightIter = sv.data;
	const double* rightEnd = sv.limit;
	while (leftIter != leftEnd && rightIter != rightEnd) {
		*leftIter = *rightIter;
		leftIter++;
		rightIter++;
	}

	delete &sv;
	delete this;
}

void SubVector::operator=(double d) {
	for (double* i = data; i != limit; ++i) {
		*i = d;
	}
	delete this;
}


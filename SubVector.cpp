
#include "SubVector.h"

using namespace std;

SubVector::SubVector() {
	data = limit = 0;
}

SubVector::SubVector(double* d, double* l) {
	data = d;
	limit = l;
}

SubVector& SubVector::operator=(const SubVector& sv) {
	if (this != &sv) {
		data = sv.data;
		limit = sv.limit;
	}
	return *this;
}

SubVector::~SubVector() {
	data = limit = 0;
}


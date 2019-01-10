

#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <vector>
// #include <utility>

using namespace std;

class SubMatrix {
	friend class Matrix;

private:
	typedef vector<double>::const_iterator vdc_iter;
	vector<pair<vdc_iter, vdc_iter>> limits;
};

#endif



#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <vector>

using namespace std;

class SubMatrix {
public:
	typedef vector<double>::const_iterator vdc_iter;

// private:
	vector<pair<vdc_iter, vdc_iter>> limits;
};

#endif

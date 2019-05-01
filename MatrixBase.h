
#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include <vector>

using namespace std;

class MatrixBase {

friend class MatrixBuilder;

public:

	int size(int dim = 0) const;
	double& operator()(int, int);
	const double& operator()(int, int) const;
	// virtual void operator=(double) = 0;
	// virtual void Print(ostream&) const = 0;
	// virtual void Print(ofstream&) const = 0;

protected:
	int nRows;
	int nCols;
	int top;
	int down;
	int left;
	int right;
	vector<vector<double>> data;
};

#endif

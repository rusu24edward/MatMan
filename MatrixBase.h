
#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MatrixBase {

// friend class MatrixBuilder;

public:

	double& operator()(int, int);
	const double& operator()(int, int) const;
	void operator=(double);
	int size(int dim = 0) const;

	void Print(ostream&) const;
	friend ostream& operator<<(ostream&, const MatrixBase&);
	void Print(ofstream&) const;
	friend ofstream& operator<<(ofstream&, const MatrixBase&);

protected:
	int nRows;
	int nCols;
	int top;
	int down;
	int left;
	int right;
	vector<vector<double>>* data_ptr;
};

#endif

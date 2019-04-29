
#ifndef MATRIXBASE_H
#define MATRIXBASE_H

// #include "MatrixBuilder.h"
// class MatrixBuilder;

using namespace std;

class MatrixBase {

friend class MatrixBuilder;

public:

	int size(int dim = 0) const;
	// virtual void operator=(double) = 0;
	// virtual void Print(ostream&) const = 0;
	// virtual void Print(ofstream&) const = 0;

protected:
	int nRows;
	int nCols;
};

#endif

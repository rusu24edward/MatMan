
#ifndef MATRIXBASE_H
#define MATRIXBASE_H

class MatrixBase {

public:

	// virtual void operator=(double) = 0;
	int size(int dim = 0) const;
	// virtual void Print(ostream&) const = 0;
	// virtual void Print(ofstream&) const = 0;

protected:
	int nRows;
	int nCols;
};

#endif

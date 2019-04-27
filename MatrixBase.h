
#ifndef MATRIXBASE_H
#define MATRIXBASE_H

class MatrixBase {

public:

	// virtual void operator=(double) = 0;
	// virtual void Print(ostream&) const = 0;
	// virtual void Print(ofstream&) const = 0;

protected:
	int sizeHelper(int dim) const;
	int nRows;
	int nCols;
};

#endif

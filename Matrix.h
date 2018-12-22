
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
public:

	Matrix() {
		reset();
	}

	Matrix(int r, int c) {
		nRows = r;
		nCols = c;
	}

	Matrix(const Matrix& mat) {
		copy(mat);
	}

	Matrix& operator=(const Matrix& mat) {
		copy(mat);
	}

	~Matrix() {
		reset();
	}


	// nRows
	const int getRows() const {
		return nRows;
	}
	int getRows() {
		return nRows;
	}
	void setRows(int r) {
		nRows = r;
	}

	// nCols
	const int getCols() const {
		return nCols;
	}
	int getCols() {
		return nCols;
	}
	void setCols(int c) {
		nCols = c;
	}


	// print
	void Print() {
		std::cout << "\n\tRows: " << nRows << std::endl;
		std::cout << "\tCols: " << nCols << std::endl;
	}


private:

	// helper functions
	void copy(const Matrix& mat) {
		nRows = mat.getRows();
		nCols = mat.getCols();
	}

	void reset() {
		nRows = 0;
		nCols = 0;
	}

	// --- Underlying Data --- //
	int nRows;
	int nCols;
};

#endif

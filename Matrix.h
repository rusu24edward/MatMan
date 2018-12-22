
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

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
	void Print() const {
		cout << "\n\tRows: " << nRows << endl;
		cout << "\tCols: " << nCols << endl;
	}

	friend ostream & operator<<(ostream &streamer, const Matrix& mat) {
		mat.Print();
		return streamer;
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

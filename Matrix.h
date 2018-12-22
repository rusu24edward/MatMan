
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:

	Matrix() {
		reset();
	}

	Matrix(int r, int c) {
		reset(r, c);
	}

	Matrix(int r, int c, double value) {
		reset(r, c, value);
	}

	Matrix(const vector<vector<double>>& d) {
		copy(d);
	}

	Matrix& operator=(const vector<vector<double>>& d) {
		copy(d);
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

	// data
	const vector<vector<double>>& getData() const {
		return data;
	}
	vector<vector<double>>& getData() {
		return data;
	}
	void setData(const vector<vector<double>>& d) {
		data = d;
	}


	// print
	void Print() const {
		cout << "\n\tRows: " << nRows << endl;
		cout << "\tCols: " << nCols << endl;
		for (vector<vector<double>>::const_iterator
			 i = data.begin(); i != data.end(); ++i) {
			cout << "[ ";
			for (vector<double>::const_iterator
				 j = i->begin(); j != i->end(); ++j) {
				cout << *j << " ";
			}
			cout << "]" << endl;
		}
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
		data = mat.getData();
	}

	void copy(const vector<vector<double>>& d) {
		int checkNumberOfColumns = d[0].size();
		for (int i = 1; i < d.size(); ++i) {
			if (d[i].size() != checkNumberOfColumns)
				reset();
		}
		nRows = d.size();
		nCols = checkNumberOfColumns;
		data = d;
	}

	void reset() {
		nRows = 0;
		nCols = 0;
		data = vector<vector<double>>();
	}

	void reset(int r, int c) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, 0.));
	}

	void reset(int r, int c, double value) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, value));
	}



	// --- Underlying Data --- //
	int nRows;
	int nCols;

	vector<vector<double>> data;

	//TODO: add matrix name
};

#endif


#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>


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

	// name
	const string& getName() const {
		return name;
	}
	string& getName() {
		return name;
	}
	void setName(const string& n) {
		name = n;
	}


	// element insertion/extraction
	const double extract(int r, int c) const {
		return data[r][c];
	}
	const double operator()(int r, int c) const {
		return data[r][c];
	}
	double extract(int r, int c) {
		return data[r][c];
	}
	double operator()(int r, int c) {
		return data[r][c];
	}
	void insert(int r, int c, double value) {
		data[r][c] = value;
	}
	// In order to make this function happen, I need to setup iterators that point
	// to a specific location or a range of locations (including the entire thing)
	// that need to be updated.
	// TODO: implement iterators
	// void insert(double value) {
		// insert the value at the location of the iterators.
	//}
	// void operator=(double value) {
		// insert the value at the location of the iterators.
	// }


	// print
	void Print() const {
		cout << "\n\tRows: " << nRows << endl;
		cout << "\tCols: " << nCols << endl;
		for (vector<vector<double>>::const_iterator
			 i = data.begin(); i != data.end(); ++i) {
			cout << "\t\t[ ";
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
		name = "NotNamed";
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
		name = "NotNamed";
	}

	void reset() {
		nRows = 0;
		nCols = 0;
		data = vector<vector<double>>();
		name = "NotNamed";
	}

	void reset(int r, int c) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, 0.));
		name = "NotNamed";
	}

	void reset(int r, int c, double value) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, value));
		name = "NotNamed";
	}



	// --- Underlying Data --- //
	int nRows;
	int nCols;
	string name;

	vector<vector<double>> data;
};

#endif

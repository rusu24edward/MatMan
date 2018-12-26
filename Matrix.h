
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



	// --- Opeartor tests --- //
	Matrix& operator()(int t, int b, int l, int r, const string& call) {
		cout << "Function operator: " << call << endl;
		setIterators(t, b+1, l, r+1);
		return *this;
	}

	// Very close to the above = operator. Here, I don't use a constant RHS, but I
	// will want to in the final version, so the code must be the same.
	// I modify the copy helper function to just copy the stuff captured
	// between the iterators.
	void operator=(Matrix& mat_in) {
		cout << "Equals operator" << endl;
		cout << mat_in << endl;
		// loop over the iterators and copy the values into data.
		for (int i = topLimit, ii = mat_in.topLimit; i < bottomLimit; ++i, ++ii) {
			for (int j = leftLimit, jj = mat_in.leftLimit; j < rightLimit; ++j, ++jj) {
				data[i][j] = mat_in.extract(ii, jj);
			}
		}
		setIterators();
		mat_in.setIterators();
	}




	// print
	void Print() const {
		cout << name << endl;
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
		cout << "\tIterators: (" << topLimit << ", " << bottomLimit << ", "
			 << leftLimit << ", " << rightLimit << ")" << endl;
	}

	friend ostream & operator<<(ostream &streamer, const Matrix& mat) {
		mat.Print();
		return streamer;
	}




	// --- I want to make these private... --- //

	void setIterators() {
		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;
	}

	void setIterators(int t, int b, int l, int r) {
		topLimit = t;
		bottomLimit = b;
		leftLimit = l;
		rightLimit = r;
	}


	int topLimit, bottomLimit, leftLimit, rightLimit;

private:

	// helper functions
	void copy(const Matrix& mat) {
		nRows = mat.getRows();
		nCols = mat.getCols();
		data = mat.getData();
		setIterators();
		name = "NotNamed";
	}

	void copy(const vector<vector<double>>& d) {
		int checkNumberOfColumns = d[0].size();
		for (int i = 1; i < d.size(); ++i) {
			if (d[i].size() != checkNumberOfColumns)
				// Output a warning message
				reset();
		}
		nRows = d.size();
		nCols = checkNumberOfColumns;
		data = d;
		setIterators();
		name = "NotNamed";
	}

	void reset() {
		nRows = 0;
		nCols = 0;
		data = vector<vector<double>>();
		setIterators();
		name = "NotNamed";
	}

	void reset(int r, int c) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, 0.));
		setIterators();
		name = "NotNamed";
	}

	void reset(int r, int c, double value) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, value));
		setIterators();
		name = "NotNamed";
	}



	// --- Underlying Data --- //
	int nRows;
	int nCols;

	vector<vector<double>> data;


	string name;
};

#endif

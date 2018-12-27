
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Matrix {
public:

	Matrix() {
		nRows = 0;
		nCols = 0;
		data = vector<vector<double>>();

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		name = UNAMED;
	}

	Matrix(int r, int c) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, 0.));

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		name = UNAMED;
	}

	Matrix(int r, int c, double value) {
		nRows = r;
		nCols = c;
		data = vector<vector<double>>(r, vector<double>(c, value));

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		name = UNAMED;
	}

	Matrix(const Matrix& mat) {
// cout << "Using constant copy constructor" << endl;
		name = UNAMED;
		nRows = mat.bottomLimit - mat.topLimit;
		nCols = mat.rightLimit - mat.leftLimit;

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		data = vector<vector<double>>(nRows, vector<double>(nCols, 0.));

		for (int i = topLimit, ii = mat.topLimit; i < bottomLimit; ++i, ++ii) {
			for (int j = leftLimit, jj = mat.leftLimit; j < rightLimit; ++j, ++jj) {
				data[i][j] = mat.extract(ii, jj);
			}
		}
	}

	Matrix(const vector<vector<double>>& d) {
		int checkNumberOfColumns = d[0].size();
		for (int i = 1; i < d.size(); ++i) {
			if (d[i].size() != checkNumberOfColumns) {

				// Reset
				nRows = 0;
				nCols = 0;
				data = vector<vector<double>>();

				topLimit = 0;
				bottomLimit = nRows;
				leftLimit = 0;
				rightLimit = nCols;

				name = UNAMED;

				throw "WARNING: Inconsistent number of columns in input argument.";
			}
		}

		nRows = d.size();
		nCols = checkNumberOfColumns;
		data = d;

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		name = UNAMED;
	}

	~Matrix() {
		nRows = 0;
		nCols = 0;
		data = vector<vector<double>>();

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		name = "";
	}

	// name
	const string& getName() const {
		return name;
	}
	void setName(const string& n) {
		name = n;
	}



	Matrix& operator=(const vector<vector<double>>& d) {
// cout << "Using constant vector assignment operator" << endl;
		int checkNumberOfColumns = d[0].size();
		for (int i = 1; i < d.size(); ++i) {
			if (d[i].size() != checkNumberOfColumns) {
				throw "ERROR: Inconsistent number of columns in input argument.";
			}
		}
		nRows = d.size();
		nCols = checkNumberOfColumns;
		data = d;

		topLimit = 0;
		bottomLimit = nRows;
		leftLimit = 0;
		rightLimit = nCols;

		return *this;
	}


	// element insertion/extraction
	const double extract(int r, int c) const {
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR: Attempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}
	const double operator()(int r, int c) const {
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR: Attempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}
	void insert(int r, int c, double value) {
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR: Attempting to access elements outside the matrix range.";
		}
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
		cout << endl << name << endl;
		cout << "\tRows: " << nRows << endl;
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



private:

	// --- Underlying Data --- //
	int nRows;
	int nCols;
	vector<vector<double>> data;
	string name;

	int topLimit;
	int bottomLimit;
	int leftLimit;
	int rightLimit;

	const string UNAMED = "UNAMED";

};

#endif

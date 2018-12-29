
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
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
				throw "ERROR:  "
					  "Matrix::Matrix(const vector<vector<double>>&)\n"
					  "\tInconsistent number of columns in input argument.";

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
				throw "ERROR:  "
					  "Matrix& Matrix::operator=(const vector<vector<double>>&)\n"
					  "\tInconsistent number of columns in input argument.";
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
			throw "ERROR:  "
				  "const double Matrix::extract(int, int) const\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}
	const double operator()(int r, int c) const {
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR:  "
				  "const double Matrix::operator()(int, int) const\n"
				  "\tAttempting to access elements outside the matrix range.";
		}
		return data[r][c];
	}
	void insert(int r, int c, double value) {
		if (r >= bottomLimit || c >= rightLimit) {
			throw "ERROR:  "
				  "void Matrix::insert()(int, int, double)\n"
				  "\tAttempting to access elements outside the matrix range.";
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
	void Print(ostream& streamer) const {
		// TODO: check if state of stream is good
		streamer << endl << name << endl;
		streamer << "\tRows: " << nRows << endl;
		streamer << "\tCols: " << nCols << endl;
		for (vector<vector<double>>::const_iterator
			 i = data.begin(); i != data.end(); ++i) {
			streamer << "\t\t[ ";
			for (vector<double>::const_iterator
				 j = i->begin(); j != i->end(); ++j) {
				streamer << *j << " ";
			}
			streamer << "]" << endl;
		}
		streamer << "\tIterators: (" << topLimit << ", " << bottomLimit << ", "
			 << leftLimit << ", " << rightLimit << ")" << endl;
	}

	friend ostream& operator<<(ostream& streamer, const Matrix& mat) {
		mat.Print(streamer);
		return streamer;
	}

	void Print(fstream& fileOut) const {
		// TODO: check if file is open
		fileOut << endl << name << endl;
		fileOut << "\tRows: " << nRows << endl;
		fileOut << "\tCols: " << nCols << endl;
		for (vector<vector<double>>::const_iterator
			 i = data.begin(); i != data.end(); ++i) {
			fileOut << "\t\t[ ";
			for (vector<double>::const_iterator
				 j = i->begin(); j != i->end(); ++j) {
				fileOut << *j << " ";
			}
			fileOut << "]" << endl;
		}
		fileOut << "\tIterators: (" << topLimit << ", " << bottomLimit << ", "
			 << leftLimit << ", " << rightLimit << ")" << endl;
	}

	friend fstream& operator<<(fstream& fileOut, const Matrix& mat) {
		mat.Print(fileOut);
		return fileOut;
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

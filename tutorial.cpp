
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matrix.h"
#include "SubMatrix.h"


int RunTests(const std::string&);
int CompareAgainstBaseline(const std::string&);
int TestMatrix();
int TestSubMatrix();
void Print(const Matrix&, ofstream&);
void Print(const SubMatrix&, ofstream&);



// Run the program, which right now just runs a test suite. Inputs are not used.
// @param int argc - the number of input arguments
// @param char** argv - an array of "strings" which are the input arguments
// @return int - the number of tests that fail.
int main (int argc, char** argv) {

	std::vector<std::string> testNames;
	// TODO: testNames.push_back("TestsTest"); // For testing the testing
	testNames.push_back("MatrixTest");
	testNames.push_back("SubMatrixTest");
	// testNames.push_back("VectorTest");
	// testNames.push_back("AdvancedMatrixTest");

	// Run all the tests
	int finalStatus = 0;
	for (std::vector<std::string>::const_iterator iter = testNames.begin();
		 iter != testNames.end(); ++iter) {
		int status = RunTests(*iter);
		if (status == 0) { // If the test completed, test the output against the baseline
			status = CompareAgainstBaseline(*iter);
		}
		finalStatus += status;
	}

	if (finalStatus != 0) {
		std::cout << "Failed " << finalStatus << " test(s)!" << std::endl;
	} else {
		std::cout << "Passed all tests!" << std::endl;
	}

	return finalStatus;
}



// Run the specified test.
// @param const std::string& testName - the name of the tests to run
// @return int - 1 if test failed, 0 if test passed.
int RunTests(const std::string& testName) {
	int status = 0;
	if (testName == "MatrixTest") {
		status = TestMatrix();
	} else if (testName == "SubMatrixTest") {
		status = TestSubMatrix();
	} else {
		std::cout << "WARNING: " << testName << " does not exist." << std::endl;
	}
	return status;
}

// Compare the "current" file against the "baseline" file.
// @param const std::string& testName - the name of the test files to compare
// @return int - 1 if the files are different, 0 if the files are the same
int CompareAgainstBaseline(const std::string& testName) {
	int status = 0;

	std::string currentFileName = "current/" + testName + ".out";
	std::ifstream currentFile(currentFileName);
	if (!currentFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << currentFileName << "!" << std::endl;
		return 1;
	}

	std::string baselineFileName = "baselines/" + testName + ".out";
	std::ifstream baselineFile(baselineFileName);
	if (!baselineFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << baselineFileName << "!" << std::endl;
		return 1;
	}

	string currentString, baselineString;
    do {
    	currentFile >> currentString;
    	baselineFile >> baselineString;
		if (currentString != baselineString) {
			status = 1;
			std::cout << "FAILURE: " << testName << " did not pass!" << std::endl;
			break;
		}
      } while (!currentFile.eof() || !baselineFile.eof());

    // TODO: if passed the test, then delete the currentFile.

	currentFile.close();
	baselineFile.close();

    if (status == 0) { // If passed the test, delete the currentFile
		if(std::remove(currentFileName.c_str()) != 0) {
			std::cout << "FAILURE: Cannot remove " << currentFileName << "!"
					  << std::endl;
			status = 1;
		}
    }

	return status;
}

// The test for the SubMatrix class.
// @return int - 1 if failed, 0 if passed.
int TestSubMatrix() {

	int status = 1;

	std::string testFileName = "current/SubMatrixTest.out";
	std::ofstream outFile(testFileName);
	if (!outFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
		return 1;
	}



	// Matrix mat1(4,6);
	// mat1.setName("Matrix 1");
	// for (int i = 0; i < 4; ++i) {
	// 	for (int j = 0; j < 6; ++j) {
	// 		mat1.insert(i,j,(i+1)*(j+1));
	// 	}
	// }
	// outFile << "Built each element" << std::endl;
	// Print(mat1, outFile);
	// mat1.DEBUG_PrintFromLimits();

	// Matrix mat2(mat1);
	// mat2.setName("Matrix 2");
	// outFile << "Built from copy constructor" << std::endl;
	// mat2.DEBUG_PrintFromLimits();

	// mat2 = mat1;
	// outFile << "Built from assignment operator" << std::endl;
	// mat2.DEBUG_PrintFromLimits();

	// Matrix mat1(4,4,2);
	// Matrix mat2(4,4,-1);
	// Matrix mat3(2,2,0);

	// // submatrix = submatrix
	// mat1(1,2,1,2) = mat2(1,2,1,2);
	// // submatrix = matrix
	// mat2(0,1,0,1) = mat3;
	// // matrix constructed with submatrix
	// Matrix mat4 = mat2(2,3,2,3);

	Matrix mat1(4,4,2);
	mat1.setName("Matrix 1");
	Matrix mat2(4,4,-1);
	mat2.setName("Matrix 2");
	Matrix mat3(2,2,0);
	mat3.setName("Matrix 3");

	Matrix* mat4 = mat1.extract(0,1,0,1);
	mat4->setName("Matrix 4 Pointer:");
	mat4->Print(std::cout);

	Matrix* mat5 = mat2(1, 2, 1, 2);
	mat5->Print(std::cout);
	delete mat4;
	delete mat5;

	Matrix mat6 = mat1(2,3,2,3);
	mat6.setName("Matrix 6");
	mat6.Print(std::cout);



	outFile.close();
	status = 0;
	return status;
}

// The test for the Matrix class.
// @return int - 1 if failed, 0 if passed.
int TestMatrix() {

	int status = 1;

	std::string testFileName = "current/MatrixTest.out";
	std::ofstream outFile(testFileName);
	if (!outFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
		return 1;
	}

	std::vector<std::vector<double>> vec1(9, vector<double>(2, -1.0));
	std::vector<std::vector<double>> vec2;
	vec2.push_back(vector<double>(5));
	vec2.push_back(vector<double>(3));
	vec2.push_back(vector<double>(5));

	try{

		Matrix mat1;
		Print(mat1, outFile);

		Matrix mat2(2,2);
		mat2.setName("Matrix 2");
		Print(mat2, outFile);

		mat2 = vec1;
		Print(mat2, outFile);

		Matrix mat3(mat1);
		mat3.setName("Matrix 3");
		Print(mat3, outFile);

		Matrix mat4 = mat1;
		mat4.setName("Matrix 4");
		Print(mat4, outFile);

		Matrix mat5(2,2,1.);
		mat5.setName("Matrix 5");
		Print(mat5, outFile);

		Matrix mat6 = mat5;
		mat6.setName("Matrix 6");
		Print(mat6, outFile);

		Matrix mat7(vec1);
		mat7.setName("Matrix 7");
		Print(mat7, outFile);

		Matrix mat8 = vec1;
		mat8.setName("Matrix 8");
		Print(mat8, outFile);

		Matrix mat9(2,1);
		mat9.setName("Matrix 9");
		Print(mat9, outFile);

		Matrix mat10(4,2);
		mat10.setName("Matrix 10");
		for (int i = 0; i < 4; ++i) {
			mat10.insert(i,0,i);
		}
		for (int i = 0; i < 4; ++i) {
			mat10.insert(i,1,10-i);
		}
		Print(mat10, outFile);

		Matrix mat11(1,1);
		mat11.setName("Matrix 11");
		mat11.insert(0,0,mat10.extract(1,1));
		Print(mat11, outFile);

		outFile << "\nAttempting to construct Matrix with inconsistent vector."
				<< std::endl;
		try {
			Matrix mat12(vec2);
			mat12.setName("Matrix 12");
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}

		outFile << "\nAttempting to assign Matrix to inconsistent vector."
				  << std::endl;
		Matrix mat13 = mat9;
		mat13.setName("Matrix 13");
		try {
			mat13 = vec2;
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		Print(mat13, outFile);

		outFile << "\nAttempting to access out of range elements." << std::endl;
		Matrix mat14(3,1);
		mat14.setName("Matrix 14");
		Print(mat14, outFile);
		try {
			for (int i = 0; i < 3; ++i) {
				mat14.insert(i,0,mat5.extract(i,1));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			for (int i = 0; i < 3; ++i) {
				mat14.insert(i,0,mat5(i,1));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			for (int i = 0; i < 4; ++i) {
				mat14.insert(i,0,mat5(0,1));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		Print(mat14, outFile);

		mat14 = mat10;
		Print(mat14, outFile);

		mat14 = mat14;
		Print(mat14, outFile);

		Matrix mat15(3,3,1.);
		mat15.setName("Matrix 15");
		mat15.insert(1,1,2.);
		Print(mat15, outFile);
		mat15.insert(0.);
		Print(mat15, outFile);
		mat15 = 24.;
		Print(mat15, outFile);

		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Matrix Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Matrix Test!" << std::endl;
		status = 1;
	}

	outFile.close();
	return status;
}

// Print the specified Matrix to the specified file
// @param const Matrix& m - the Matrix to print
// @param ofstream& outFile - the file to print to.
void Print(const Matrix& m, ofstream& outFile) {
	outFile << m << std::endl;
}

// Print the specified SubMatrix to the specified file
// @param const SubMatrix& sm - the SubMatrix to print
// @param ofstream& outFile - the file to print to.
void Print(const SubMatrix& sm, ofstream& outFile) {
	outFile << sm << std::endl;
}

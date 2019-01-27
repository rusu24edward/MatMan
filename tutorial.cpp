
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matrix.h"
#include "MyVector.h"

// Might need: class SubVector;


int RunTests(const std::string&);
int CompareAgainstBaseline(const std::string&);
int TestMatrix();
void Print(const Matrix&, ofstream&);
void Print(const MyVector&, ofstream&);
int TestVector();


// Run the program, which right now just runs a test suite. Inputs are not used.
// @param int argc - the number of input arguments
// @param char** argv - an array of "strings" which are the input arguments
// @return int - the number of tests that fail.
int main (int argc, char** argv) {

	MyVector mv(10);

	std::vector<std::string> testNames;
	// TODO: testNames.push_back("TestsTest"); // For testing the testing
	testNames.push_back("MatrixTest");
	testNames.push_back("VectorTest");
	testNames.push_back("AdvancedMatrixTest");

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
	} else if (testName == "VectorTest") {
		status = TestVector();
	} else {
		std::cout << "WARNING: " << testName << " does not exist." << std::endl;
		status = 1;
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

		Matrix mat9(1,2);
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

		Matrix mat16 = mat10(0,2,0,1);
		mat16.setName("Matrix 16");
		Print(mat16, outFile);

		mat16 = mat10(3,3,0,1);
		Print(mat16, outFile);

		Matrix mat17(mat15(1,1,1,1));
		mat17.setName("Matrix 17");
		Print(mat17, outFile);

		vector<int> tempSize = mat10.size();
		outFile << "Size of " << mat10.getName() << ": " << "[ " << tempSize[0]
				<< " " << tempSize[1] << " ]" << std::endl;
		outFile << "Length of " << mat14.getName() << ": " << mat14.length()
				<< std::endl;
		outFile << "Length of " << mat9.getName() << ": " << mat9.length()
				<< std::endl;
		outFile << "Number of rows in " << mat16.getName() << ": "
				<< mat16.size(1) << std::endl;
		outFile << "Number of columns in " << mat16.getName() << ": "
				<< mat16.size(2) << std::endl;

		outFile << "Attempting to query bad dimension size." << std::endl;
		try {
			mat16.size(0);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			mat16.size(3);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}


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



// The test for the Vector class.
// @return int - 1 if failed, 0 if passed.
int TestVector() {
	int status = 1;

	std::string testFileName = "current/VectorTest.out";
	std::ofstream outFile(testFileName);
	if (!outFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
		return 1;
	}

	std::vector<double> helperVec1(3,6.);

	try{

		MyVector vec1;
		Print(vec1, outFile);

		MyVector vec2(2);
		vec2.setName("Vector 2");
		Print(vec2, outFile);

		MyVector vec3(5,-2.);
		vec3.setName("Vector 3");
		Print(vec3, outFile);

		MyVector vec4(helperVec1);
		vec4.setName("Vector 4");
		Print(vec4, outFile);

		MyVector vec5(vec4);
		vec5.setName("Vector 5");
		Print(vec5, outFile);

		vec5 = vec3;
		Print(vec5,outFile);

		vec5 = helperVec1;
		Print(vec5, outFile);

		outFile << "\nAttempting to access out of range elements." << std::endl;
		MyVector vec6(3);
		vec6.setName("Vector 6");
		Print(vec6, outFile);
		try {
			for (int i = 0; i < 3; i++) {
				vec6.insert(i,vec2.extract(i));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			for (int i = 0; i < 3; ++i) {
				vec6.insert(i,vec2(i));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			for (int i = 0; i < 4; ++i) {
				vec6.insert(i,vec2(0));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			MyVector vec_t = vec6(3,2);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			MyVector vec_t = vec6(-1,2);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			MyVector vec_t = vec6(2,7);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		Print(vec6, outFile);

		MyVector vec7(5,-1.);
		vec7.setName("Vector 7");
		vec7.insert(1,vec4(2));
		Print(vec7, outFile);
		vec7.insert(-2.0);
		Print(vec7, outFile);
		vec7 = 24;
		Print(vec7, outFile);


		MyVector vec8(7);
		vec8.setName("Vector 8");
		for (int i = 0; i < 7; ++i) {
			vec8.insert(i, 10-i);
		}
		Print(vec8, outFile);

		MyVector vec9(4);
		vec9.setName("Vector 9");
		for (int i = 0; i < 4; ++i) {
			vec9.insert(i,2*i);
		}
		Print(vec9, outFile);

		MyVector vec10(vec8(2,4));
		vec10.setName("Vector 10");
		Print(vec10, outFile);

		vec10 = vec9(0,3);
		Print(vec10, outFile);

		vec10(1,2) = vec2;
		Print(vec10, outFile);

		vec10(1,3) = vec8(4,6);
		Print(vec10, outFile);

		vec10(3) = 11;
		Print(vec10, outFile);

		vec10(0,1) = -1;
		Print(vec10, outFile);



		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Vector Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Vector Test!" << std::endl;
		status = 1;
	}

	outFile.close();
	return status;
}

void Print(const MyVector& v, ofstream& outFile) {
	outFile << v << std::endl;
}

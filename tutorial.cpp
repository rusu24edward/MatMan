

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matrix.h"

std::vector<std::string> testFileNames;

int RunTests(const std::string&);
int CompareAgainstBaseline(const std::string&);
int TestMatrix();
void Print(const Matrix&, ofstream&);




int main (int argc, char** argv) {

	std::cout << "Hello World!" << std::endl;


	// TODO: testFileNames.push_back("TestsTest"); // For testing the testing
	testFileNames.push_back("MatrixTest");
	// testFileNames.push_back("VectorTest");
	// testFileNames.push_back("AdvancedMatrixTest");

	// Run all the tests
	int finalStatus = 0;
	for (std::vector<std::string>::const_iterator iter = testFileNames.begin();
		 iter != testFileNames.end(); ++iter) {
		int status = RunTests(*iter);
		if (status == 0) { // If the test completed, test the output against the baseline
			status = CompareAgainstBaseline(*iter);
		}
		finalStatus += status;
	}

	if (finalStatus != 0) {
		std::cout << "Failed " << finalStatus << " test(s)!" << std::endl;
	}

	return finalStatus;
}




int RunTests(const std::string& testName) {
	int status = 0;
	if (testName == "MatrixTest") {
		status = TestMatrix();
	} else {
		std::cout << "WARNING: " << testName << " does not exist." << std::endl;
	}
	return status;
}

int CompareAgainstBaseline(const std::string& testName) {
	int status = 0;

	std::string currentFileName = "current/" + testName + ".out";
	std::ifstream currentFile(currentFileName);
	if (!currentFile.is_open()) {
		std::cout << "FAILURE: Cannot open current/" << testName << ".out!"
				  << std::endl;
		return 1;
	}

	std::string baselineFileName = "baselines/" + testName + ".out";
	std::ifstream baselineFile(baselineFileName);
	if (!baselineFile.is_open()) {
		std::cout << "FAILURE: Cannot open baseline/" << testName << ".out!"
				  << std::endl;
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

	return status;
}




int TestMatrix() {

	int status = -1;

	std::string testFileName = "current/" + testFileNames[0] + ".out";
	std::ofstream outFile;
	outFile.open(testFileName);

	try{

		Matrix mat1;
		Print(mat1, outFile);

		Matrix mat2(2,2);
		mat2.setName("Matrix 2");
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

		std::vector<std::vector<double>> vec1(9, vector<double>(2, -1.0));
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

		mat2 = vec1;
		Print(mat2, outFile);

		std::vector<std::vector<double>> vec2;
		vec2.push_back(vector<double>(5));
		vec2.push_back(vector<double>(3));
		vec2.push_back(vector<double>(5));
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
		try {
			mat9 = vec2;
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		Print(mat9, outFile);

		outFile << "\nAttempting to access out of range elements." << std::endl;
		Matrix mat13(3,1);
		mat13.setName("Matrix 13");
		try {
			for (int i = 0; i < 3; ++i) {
				mat13.insert(i,0,mat5.extract(i,1));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			for (int i = 0; i < 3; ++i) {
				mat13.insert(i,0,mat5(i,1));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			for (int i = 0; i < 4; ++i) {
				mat13.insert(i,0,mat5(0,1));
			}
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		Print(mat13, outFile);

		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Matrix Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Matrix Test!" << std::endl;
		status = 1;
	}

	outFile.close();
	return status;
}

void Print(const Matrix& m, ofstream& outFile) {
	outFile << m << std::endl;
}

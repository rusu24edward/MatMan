
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Vector.h"
#include "SubVector.h"


int RunTests(const std::string&);
int CompareAgainstBaseline(const std::string&);
int TestVector();
void Print(const Vector&, ofstream&);
void Print(const SubVector&, ofstream&);


// Run the program, which right now just runs a test suite. Inputs are not used.
// @param int argc - the number of input arguments
// @param char** argv - an array of "strings" which are the input arguments
// @return int - the number of tests that fail.
int main (int argc, char** argv) {

	std::vector<std::string> testNames;
	// TODO: testNames.push_back("TestsTest"); // For testing the testing
	testNames.push_back("VectorTest");

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
		// status = TestMatrix();
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

	std::vector<double> helperVec1(3,7.);
	std::vector<double> helperVec2(3,1.);

	try{

		// Vector construction and assignment
		Vector vec1;
		Print(vec1, outFile);

		Vector vec2(2);
		vec2.setName("Vector 2");
		Print(vec2, outFile);

		Vector vec3(5,-2.);
		vec3.setName("Vector 3");
		Print(vec3, outFile);

		Vector vec4(helperVec1);
		vec4.setName("Vector 4");
		Print(vec4, outFile);

		Vector vec5(vec4);
		vec5.setName("Vector 5");
		Print(vec5, outFile);

		vec5 = helperVec2;
		Print(vec5, outFile);

		vec5 = vec3;
		Print(vec5, outFile);

		vec5 = -100;
		Print(vec5, outFile);

		// Element access
		Vector vec6(4);
		vec6.setName("Vector 6");
		for (int i = 0; i < 4; ++i) {
			vec6(i) = -(i+1)*6;
		}
		vec6(2) = vec6(0);
		vec6(1) = vec6(3);
		Print(vec6, outFile);

		// SubVector access
		Print(vec6(1,2), outFile);
		Vector vec7(vec6(1,3));
		vec7.setName("Vector 7");
		Print(vec7, outFile);

		vec7 = vec6(0,1);
		Print(vec7, outFile);

		// Vector vec8(11,12);
		// vec8.setName("Vector 8");
		// Print(vec8, outFile);

		// vec8(1,4) = vec6;
		// Print(vec8, outFile);

		// vec8(8,10) = vec8(1,3);
		// Print(vec8, outFile);

		// vec8(6,7) = vec8(7,8);
		// Print(vec8, outFile);

		// vec8(0,1) = vec2;
		// Print(vec8, outFile);

		// Print(vec8(0,3), outFile);

		// vec8(6,8) = -4;
		// Print(vec8, outFile);

		// Test all the error catches
		Vector vec9(3);
		try {
			vec9(4) = 5;
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			Print(vec9(1,6), outFile);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		try {
			Print(vec9(1,0), outFile);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}
		// try {
		// 	vec9(0,1) = vec8(0,2);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }
		// try {
		// 	vec9(0,2) = vec3;
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }

		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Vector Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Vector Test!" << std::endl;
		status = 1;
	}

	outFile.close();
	return status;
}

void Print(const Vector& v, ofstream& outFile) {
	outFile << v << std::endl;
}

void Print(const SubVector& sv, ofstream& outFile) {
	outFile << sv << std::endl;
}

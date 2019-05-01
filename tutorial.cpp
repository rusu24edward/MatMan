
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matrix.h"
// #include "MatrixBuilder.h"
// #include "MatrixUtils.h"
// #include "Reader.h"

#include "Enums.h"


int RunTests(const std::string&);
int CompareAgainstBaseline(const std::string&);
int TestMatrix();
// int TestMatrixBuilder();
// int TestMatrixMultiplication();
// int TestMatrixAdditionAndSubtraction();
// int TestMatrixNorms();
// int TestMatrixReduction();
// int TestMatrixTranspose();
// int TestReader();
void Print(const Matrix&, ofstream&);


// Run the program, which right now just runs a test suite. Inputs are not used.
// @param int argc - the number of input arguments
// @param char** argv - an array of "strings" which are the input arguments
// @return int - the number of tests that fail.
int main (int argc, char** argv) {

	std::vector<std::string> testNames;
	// TODO: testNames.push_back("TestsTest"); // For testing the testing
	testNames.push_back("MatrixTest");
	testNames.push_back("TestMatrixBuilder");
	// testNames.push_back("TestMatrixMultiplication");
	// testNames.push_back("TestMatrixAdditionAndSubtraction");
	// testNames.push_back("TestMatrixNorms");
	// testNames.push_back("TestMatrixReduction");
	// testNames.push_back("TestMatrixTranspose");
	// testNames.push_back("ReaderTest");

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
	// } else if (testName == "TestMatrixBuilder") {
	// 	status = TestMatrixBuilder();
	// } else if (testName == "TestMatrixMultiplication") {
	// 	status = TestMatrixMultiplication();
	// } else if (testName == "TestMatrixAdditionAndSubtraction") {
	// 	status = TestMatrixAdditionAndSubtraction();
	// } else if (testName == "TestMatrixNorms") {
	// 	status = TestMatrixNorms();
	// } else if (testName == "TestMatrixReduction") {
	// 	status = TestMatrixReduction();
	// } else if (testName == "TestMatrixTranspose") {
	// 	status = TestMatrixTranspose();
	// } else if (testName == "ReaderTest") {
	// 	status = TestReader();
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

int TestMatrix() {
	int status = 1;

	std::string testFileName = "current/MatrixTest.out";
	std::ofstream outFile(testFileName);
	if (!outFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
		return 1;
	}

	std::vector<vector<double>> helperMat1(4, std::vector<double>(3, -2.4));
	std::vector<vector<double>> helperMat2;
	helperMat2.push_back(std::vector<double>(12));
	helperMat2.push_back(std::vector<double>(12));
	helperMat2.push_back(std::vector<double>(7));
	helperMat2.push_back(std::vector<double>(12));

	try{

		Matrix mat1;
		Print(mat1, outFile);

		Matrix mat2(3,3);
		mat2.setName("Matrix 2");
		Print(mat2, outFile);

		Matrix mat3(6, 4, 11);
		mat3.setName("Matrix 3");
		Print(mat3, outFile);

		Matrix mat4(helperMat1);
		mat4.setName("Matrix 4");
		Print(mat4, outFile);

		try {
			Matrix mat5(helperMat2);
		} catch (const char* msg) {
			outFile << msg << std::endl;
		}

		Matrix mat6(mat3);
		mat6.setName("Matrix 6");
		Print(mat6, outFile);

		mat6 = helperMat1;
		Print(mat6, outFile);

		mat6 = mat2;
		Print(mat6, outFile);

		Matrix mat10;
		mat10(1,1);

		// double tmp = mat6(0,0);

		// mat6(1,1) = mat3(0,1);
		// Print(mat6, outFile);

		// try {
		// 	mat6(6,6) = 12;
		// 	Print(mat6, outFile);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }
		// try {
		// 	mat6(1,2) = mat4(10,0);
		// 	Print(mat6, outFile);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }

		// Matrix mat7(10,10);
		// mat7.setName("Matrix 7");
		// for (int i = 0; i < 10; ++i) {
		// 	for (int j = 0; j < 10; ++j) {
		// 		mat7(i,j) = (i+1)*j;
		// 	}
		// }
		// Print(mat7, outFile);

		// try {
		// 	mat7(4,3,1,2);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }
		// try {
		// 	mat7(3,4,6,4);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }
		// try {
		// 	mat7(4,11,1,2);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }
		// try {
		// 	mat7(3,4,-1,2);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }

		// Matrix mat8(mat7(3,4,2,7));
		// mat8.setName("Matrix 8");
		// Print(mat8, outFile);

		// mat8 = mat7(5,9,1,2);
		// Print(mat8, outFile);

		// mat7(1,3,1,3) = mat2;
		// Print(mat7, outFile);

		// try {
		// 	mat8(1,1,0,1) = mat6;
		// 	Print(mat8, outFile);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }

		// mat7(5,7,6,8) = mat7(0,2,7,9);
		// Print(mat7, outFile);

		// try {
		// 	mat7(1,2,3,4) = mat4(1,1,1,2);
		// 	Print(mat7, outFile);
		// } catch (const char* msg) {
		// 	outFile << msg << std::endl;
		// }

		// mat8(0,1,0,1) = -2;
		// Print(mat8, outFile);

		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Matrix Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Matrix Test!" << std::endl;
		status = 1;
	}

	outFile.close();
	return status;

}

// int TestMatrixBuilder() {
// 	int status = 1;

// 	std::string testFileName = "current/TestMatrixBuilder.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{

// 		Matrix mat1(4, 6);
// 		for (int i = 0; i < 4; ++i) {
// 			for (int j = 0; j < 6; ++j) {
// 				mat1(i,j) = (-i+1) * 2*j;
// 			}
// 		}
// 		mat1.setName("Matrix 1");
// 		Print(mat1, outFile);

// 		Matrix mat2(4, 2);
// 		for (int i = 0; i < 4; ++i) {
// 			for (int j = 0; j < 2; ++j) {
// 				mat2(i,j) = 3+2*i + 7*j;
// 			}
// 		}
// 		mat2.setName("Matrix 2");
// 		Print(mat2, outFile);

// 		Matrix mat3(3, 6, 3.);
// 		for (int i = 0; i < 3; ++i) {
// 			for (int j = 0; j < 6; ++j) {
// 				mat3(i,j) = (i+1)+(j-1);
// 			}
// 		}
// 		mat3.setName("Matrix 3");
// 		Print(mat3, outFile);

// 		Matrix combinedMatrix1 = MatrixBuilder::BuildMatrixFromCombination(mat1, mat2, MatrixCombinationType::LeftRight);
// 		combinedMatrix1.setName("Combined Matrix 1");
// 		Print(combinedMatrix1, outFile);

// 		Matrix combinedMatrix2 = MatrixBuilder::BuildMatrixFromCombination(mat2, mat1, MatrixCombinationType::LeftRight);
// 		combinedMatrix2.setName("Combined Matrix 2");
// 		Print(combinedMatrix2, outFile);

// 		Matrix combinedMatrix3 = MatrixBuilder::BuildMatrixFromCombination(mat1, mat3, MatrixCombinationType::TopDown);
// 		combinedMatrix3.setName("Combined Matrix 3");
// 		Print(combinedMatrix3, outFile);

// 		Matrix combinedMatrix4 = MatrixBuilder::BuildMatrixFromCombination(mat3, mat1, MatrixCombinationType::TopDown);
// 		combinedMatrix4.setName("Combined Matrix 4");
// 		Print(combinedMatrix4, outFile);

// 		Matrix combinedMatrix5 = MatrixBuilder::BuildMatrixFromCombination(mat2, mat1(0,3,3,4), MatrixCombinationType::TopDown);
// 		combinedMatrix5.setName("Combined Matrix 5");
// 		Print(combinedMatrix5, outFile);

// 		Matrix combinedMatrix6 = MatrixBuilder::BuildMatrixFromCombination(mat3, mat2(0,2,1,1), MatrixCombinationType::LeftRight);
// 		combinedMatrix6.setName("Combined Matrix 6");
// 		Print(combinedMatrix6, outFile);

// 		Matrix combinedMatrix7 = MatrixBuilder::BuildMatrixFromCombination(mat1(1,3,0,5), mat3, MatrixCombinationType::LeftRight);
// 		combinedMatrix7.setName("Combined Matrix 7");
// 		Print(combinedMatrix7, outFile);

// 		Matrix combinedMatrix8 = MatrixBuilder::BuildMatrixFromCombination(mat3(0,2,2,3), mat2, MatrixCombinationType::TopDown);
// 		combinedMatrix8.setName("Combined Matrix 8");
// 		Print(combinedMatrix8, outFile);

// 		Matrix combinedMatrix9 = MatrixBuilder::BuildMatrixFromCombination(mat3(0,1,0,5), mat1(2,3,0,5), MatrixCombinationType::LeftRight);
// 		combinedMatrix9.setName("Combined Matrix 9");
// 		Print(combinedMatrix9, outFile);

// 		Matrix combinedMatrix10 = MatrixBuilder::BuildMatrixFromCombination(mat1(2,2,2,2), mat2(2,2,0,0), MatrixCombinationType::TopDown);
// 		combinedMatrix10.setName("Combined Matrix 10");
// 		Print(combinedMatrix10, outFile);

// 		Matrix combinedMatrix11 = MatrixBuilder::BuildMatrixFromCombination(mat2, mat2, MatrixCombinationType::LeftRight);
// 		combinedMatrix11.setName("Combined Matrix 11");
// 		Print(combinedMatrix11, outFile);

// 		Matrix combinedMatrix12 = MatrixBuilder::BuildMatrixFromCombination(mat2, mat2, MatrixCombinationType::TopDown);
// 		combinedMatrix12.setName("Combined Matrix 12");
// 		Print(combinedMatrix12, outFile);

// 		try {
// 			Matrix combinedMatrix101 = MatrixBuilder::BuildMatrixFromCombination(mat1, mat3, MatrixCombinationType::LeftRight);
// 			combinedMatrix101.setName("Combined Matrix 101");
// 			Print(combinedMatrix101, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix102 = MatrixBuilder::BuildMatrixFromCombination(mat1, mat2, MatrixCombinationType::TopDown);
// 			combinedMatrix102.setName("Combined Matrix 102");
// 			Print(combinedMatrix102, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix103 = MatrixBuilder::BuildMatrixFromCombination(mat2, mat1(0,2,3,4), MatrixCombinationType::LeftRight);
// 			combinedMatrix103.setName("Combined Matrix 103");
// 			Print(combinedMatrix103, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix104 = MatrixBuilder::BuildMatrixFromCombination(mat3, mat2(0,2,1,1), MatrixCombinationType::TopDown);
// 			combinedMatrix104.setName("Combined Matrix 104");
// 			Print(combinedMatrix104, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix106 = MatrixBuilder::BuildMatrixFromCombination(mat3(0,2,2,3), mat2, MatrixCombinationType::LeftRight);
// 			combinedMatrix106.setName("Combined Matrix 106");
// 			Print(combinedMatrix106, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix105 = MatrixBuilder::BuildMatrixFromCombination(mat1(1,3,0,1), mat3, MatrixCombinationType::TopDown);
// 			combinedMatrix105.setName("Combined Matrix 105");
// 			Print(combinedMatrix105, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix108 = MatrixBuilder::BuildMatrixFromCombination(mat1(2,2,2,2), mat2(1,2,0,0), MatrixCombinationType::LeftRight);
// 			combinedMatrix108.setName("Combined Matrix 108");
// 			Print(combinedMatrix108, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix107 = MatrixBuilder::BuildMatrixFromCombination(mat3(0,1,0,4), mat1(2,3,0,5), MatrixCombinationType::TopDown);
// 			combinedMatrix107.setName("Combined Matrix 107");
// 			Print(combinedMatrix107, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix combinedMatrix000 = MatrixBuilder::Combine(mat1, mat2, MatrixCombinationType::LeftRight);
// 			combinedMatrix000.setName("Matrix Matrix LeftRight");
// 			Print(combinedMatrix000, outFile);
// 			Matrix combinedMatrix001 = MatrixBuilder::Combine(mat1, mat3, MatrixCombinationType::TopDown);
// 			Print(combinedMatrix001, outFile);
// 			// Matrix combinedMatrix006 = MatrixBuilder::Combine(mat2, mat1(0,3,3,4), MatrixCombinationType::TopDown);
// 			// Print(combinedMatrix006, outFile);
// 			// Matrix combinedMatrix007 = MatrixBuilder::Combine(mat3, mat2(0,2,1,1), MatrixCombinationType::LeftRight);
// 			// Print(combinedMatrix007, outFile);
// 			// Matrix combinedMatrix004 = MatrixBuilder::Combine(mat3(0,2,2,3), mat2, MatrixCombinationType::TopDown);
// 			// Print(combinedMatrix004, outFile);
// 			// Matrix combinedMatrix005 = MatrixBuilder::Combine(mat3(0,2,2,3), mat2, MatrixCombinationType::LeftRight);
// 			// Print(combinedMatrix005, outFile);
// 			// Matrix combinedMatrix002 = MatrixBuilder::Combine(mat1(2,2,2,2), mat2(2,2,0,0), MatrixCombinationType::TopDown);
// 			// Print(combinedMatrix002, outFile);
// 			// Matrix combinedMatrix003 = MatrixBuilder::Combine(mat1(2,2,2,2), mat2(1,2,0,0), MatrixCombinationType::LeftRight);
// 			// Print(combinedMatrix003, outFile);
// 		} catch (const char* msg) {
// 			std::cout << msg << std::endl;
// 		}

// 		status = 0;
// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Matrix Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Matrix Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;
// }



// int TestMatrixMultiplication() {
// 	int status = 1;

// 	std::string testFileName = "current/TestMatrixMultiplication.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{
// 		Matrix mat1(4,6);
// 		for (int i = 0; i < 4; ++i) {
// 			for (int j = 0; j < 6; ++j) {
// 				mat1(i,j) = (i+2)*(j-2);
// 			}
// 		}
// 		mat1.setName("Matrix 1");
// 		Print(mat1, outFile);

// 		Matrix mat2(6,2);
// 		for (int i = 0; i < 6; ++i) {
// 			for (int j = 0; j < 2; ++j) {
// 				mat2(i,j) = 3+i*(j+1);
// 			}
// 		}
// 		mat2.setName("Matrix 2");
// 		Print(mat2, outFile);

// 		Matrix mat3 = mat1 * mat2;
// 		mat3.setName("Matrix 3");
// 		Print(mat3, outFile);

// 		try {
// 			Matrix mat100 = mat2 * mat1;
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		Matrix mat4 = mat3 * mat2(1,2,0,1);
// 		mat4.setName("Matrix 4");
// 		Print(mat4, outFile);

// 		try {
// 			Matrix mat0 = mat3 * mat1(0,2,0,0);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		Matrix mat5 = mat1(0, 0, 2, 5) * mat3;
// 		mat5.setName("Matrix 5");
// 		Print(mat5, outFile);

// 		try {
// 			Matrix mat0 = mat1(2,3,2,4) * mat4;
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		Matrix mat6 = mat2(3,3,0,1) * mat2(0,1,1,1);
// 		mat6.setName("Matrix 6");
// 		Print(mat6, outFile);

// 		try {
// 			Matrix mat0 = mat1(0,1,0,1) * mat5(0,0,0,0);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		Matrix mat7 = MatrixBuilder::ElementMultiply(mat2(0,0,0,1), mat5);
// 		mat7.setName("Matrix 7");
// 		Print(mat7, outFile);

// 		try {
// 			Matrix mat0 = MatrixBuilder::ElementMultiply(mat3(0,1,0,1), mat5);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		Matrix mat8 = mat1 * 2;
// 		mat8.setName("Matrix 8");
// 		Print(mat8, outFile);

// 		Matrix mat9 = 0.5 * mat8;
// 		mat9.setName("Matrix 9");
// 		Print(mat9, outFile);

// 		Matrix mat10 = mat9 * 0;
// 		mat10.setName("Matrix 10");
// 		Print(mat10, outFile);

// 		Matrix mat11 = 1*mat8;
// 		mat11.setName("Matrix 11");
// 		Print(mat11, outFile);

// 		status = 0;
// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Matrix Multiplication Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Matrix Multiplication Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;
// }


// int TestMatrixAdditionAndSubtraction() {
// 	int status = 1;

// 	std::string testFileName = "current/TestMatrixAdditionAndSubtraction.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{

// 		Matrix mat1(4, 7, 2.0);
// 		for (int i = 0; i < 3; i++) {
// 			for (int j = 0; j < 6; j++) {
// 				mat1(i+1,j+1) = mat1(i,j)*(i+1)+(j+i);
// 			}
// 		}
// 		mat1.setName("Matrix 1");
// 		Print(mat1, outFile);

// 		Matrix mat2(4,7,-2);
// 		mat2.setName("Matrix 2");
// 		Print(mat2, outFile);

// 		Matrix mat3(4,4,1.0);
// 		mat3.setName("Matrix 3");
// 		Print(mat3, outFile);

// 		Matrix mat4 = mat1 + mat2;
// 		mat4.setName("Matrix 4");
// 		Print(mat4, outFile);

// 		try {
// 			Matrix mat0 = mat1 + mat3;
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		Matrix mat5 = mat1 - mat4;
// 		mat5.setName("Matrix 5");
// 		Print(mat5, outFile);

// 		try {
// 			Matrix mat0 = mat1 - mat3;
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		status = 0;

// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Matrix Addition and Subtraction Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Matrix Addition and Subtraction Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;
// }



// Test Matrix norms
// @return int - 1 if failed, 0 if passed.
// int TestMatrixNorms() {
// 	int status = 1;

// 	std::string testFileName = "current/TestMatrixNorms.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{

// 		Matrix mat1(1,1,14.0);
// 		mat1.setName("Matrix 1");
// 		Print(mat1, outFile);
// 		outFile << "Vector 2 norm is " << mat1.norm() << std::endl;

// 		Matrix mat2(4,1);
// 		mat2.setName("Matrix 2");
// 		for (int i = 0; i < 4; ++i) {
// 			mat2(i,0) = i;
// 		}
// 		Print(mat2, outFile);
// 		outFile << "Vector 2 norm is " << mat2.norm() << std::endl;

// 		Matrix mat3(1,3);
// 		mat3.setName("Matrix 3");
// 		for (int i = 0; i < 2; ++i) {
// 			mat3(0,i+1) = mat3(0,i) + 2.6;
// 		}
// 		Print(mat3, outFile);
// 		outFile << "Vector 2 norm is " << mat3.norm() << std::endl;

// 		Matrix mat4(3,5,2);
// 		mat4.setName("Matrix 4");
// 		Print(mat4, outFile);

// 		try {
// 			outFile << "Vector 2 norm is " << mat4.norm() << std::endl;
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		status = 0;
// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Matrix Norms Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Matrix Norms Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;
// }

// int TestMatrixReduction() {
// 	int status = 1;

// 	std::string testFileName = "current/TestMatrixReduction.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{

// 		Matrix mat1(3,5);
// 		for (int i = 0; i < 3; ++i) {
// 			for (int j = 0; j < 5; ++j) {
// 				mat1(i,j) = -(i+1) + 5*j;
// 			}
// 		}
// 		mat1.setName("Matrix 1");
// 		Print(mat1, outFile);

// 		Matrix mat2 = MatrixBuilder::SumReduce(mat1);
// 		mat2.setName("Matrix 2");
// 		Print(mat2, outFile);

// 		Matrix mat3 = MatrixBuilder::SumReduce(mat1, 1);
// 		mat3.setName("Matrix 3");
// 		Print(mat3, outFile);

// 		Matrix mat4 = MatrixBuilder::SumReduce(mat1, 2);
// 		mat4.setName("Matrix 4");
// 		Print(mat4, outFile);

// 		try {
// 			Matrix mat0 = MatrixBuilder::SumReduce(mat1, 3);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		status = 0;
// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Matrix Reduction Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Matrix Reduction Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;

// }

// int TestMatrixTranspose() {
// 	int status = 1;

// 	std::string testFileName = "current/TestMatrixTranspose.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{

// 		Matrix mat1(6,3);
// 		for (int i = 0; i < 6; ++i) {
// 			for (int j = 0; j < 3; ++j) {
// 				mat1(i,j) = j*j + 3*i + i*j;
// 			}
// 		}
// 		mat1.setName("Matrix 1");
// 		Print(mat1, outFile);

// 		Matrix mat2 = MatrixBuilder::Transpose(mat1);
// 		mat2.setName("Matrix 2");
// 		Print(mat2, outFile);

// 		status = 0;
// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Matrix Transpose Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Matrix Transpose Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;

// }



// The test for the Reader class.
// @return int - 1 if failed, 0 if passed.
// int TestReader() {
// 	int status = 1;

// 	std::string testFileName = "current/ReaderTest.out";
// 	std::ofstream outFile(testFileName);
// 	if (!outFile.is_open()) {
// 		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
// 		return 1;
// 	}

// 	try{
// 		Matrix mat1 = Reader::Read("ex1data1.txt", ',');
// 		mat1.setName("Matrix 1");
// 		Print(mat1,outFile);

// 		try {
// 			Matrix mat2 = Reader::Read("ex1data2.txt", ',');
// 			mat2.setName("Matrix 2");
// 			Print(mat2, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		try {
// 			Matrix mat3 = Reader::Read("ex1data3.txt", ',');
// 			mat3.setName("Matrix 3");
// 			Print(mat3, outFile);
// 		} catch (const char* msg) {
// 			outFile << msg << std::endl;
// 		}

// 		status = 0;
// 	} catch (...) {
// 		std::cout << "FAILURE: Cannot complete Reader Test!" << std::endl;
// 		outFile << "FAILURE: Cannot complete Reader Test!" << std::endl;
// 		status = 1;
// 	}

// 	outFile.close();
// 	return status;
// }



void Print(const Matrix& mat, ofstream& outFile) {
	outFile << mat << std::endl;
}



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "math.h"

#include "Matrix.h"
#include "SubMatrix.h"
#include "Reader.h"
#include "MatrixBuilder.h"

#include "Enums.h"

void Print(const Matrix&, ofstream&);
void Print(const SubMatrix&, ofstream&);
double computCost(const Matrix&, const Matrix&, const Matrix&);

// TODO: add baseline comparison test AFTER we verify against Matlab results.
int main (int argc, char** argv) {
	int status = 1; // return object
	std::string testFileName = "current/Example1.out";
	std::ofstream outFile(testFileName);
	if (!outFile.is_open()) {
		std::cout << "FAILURE: Cannot open " << testFileName << "!" << std::endl;
		return 1;
	}

	try {

		outFile << "Reading data..." << std::endl;
		Matrix data = Reader::Read("ex1data1.txt", ',');
		data.setName("Data");
		Print(data, outFile);

		outFile << "Extracting features..." << std::endl;
		int numberOfSamples = data.size(1);
		Matrix features = data(0, numberOfSamples-1, 0, 0);
		features.setName("Features");
		Print(features, outFile);

		outFile << "Extracting response" << std::endl;
		Matrix response = data(0, numberOfSamples-1, 1, 1);
		response.setName("Response");
		Print(response, outFile);

		outFile << "Adding a vector of ones to the features..." << std::endl;
		features = MatrixBuilder::BuildMatrixFromCombination(Matrix(numberOfSamples, 1, 1.0), features, MatrixCombinationType::LeftRight);
		Print(features, outFile);

		outFile << "Creating theta..." << std::endl;
		Matrix theta(2,1);
		theta.setName("theta");
		Print(theta, outFile);

		outFile << "Computing cost..." << std::endl;
		double cost = computCost(features, response, theta);
		outFile << "With theta = [0; 0], the cost is " << cost << std::endl;
		// (2a) Matrix multiplication
		// (2b) Matrix/Vector norms

		outFile << "Gradient descent..." << std::endl;
		// (3) Gradient descent
		// (3a) Matrix multiplication and subtraction
		// (3b) Matrix Sum

		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Example1 Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Example1 Test!" << std::endl;
		status = 1;
	}

	outFile.close();

	return status;
}

double computCost(const Matrix& features, const Matrix& response, const Matrix& fitParameters) {
	int numberOfSamples = response.length();
	// Matrix featuresFit = features * fitParameters;
	double cost = 0.0;
	// cost = pow((response - featuresFit).norm(), 2) / (2 * numberOfSamples);




	return cost;
}

void Print(const Matrix& mat, ofstream& outFile) {
	outFile << mat << std::endl;
}

void Print(const SubMatrix& sm, ofstream& outFile) {
	outFile << sm << std::endl;
}

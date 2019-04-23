
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "math.h"

#include "Matrix.h"
#include "SubMatrix.h"
#include "MatrixBuilder.h"
#include "MatrixUtils.h"
#include "Reader.h"

#include "Enums.h"

void Print(const Matrix&, ofstream&);
void Print(const SubMatrix&, ofstream&);
double ComputeCost(const Matrix&, const Matrix&, const Matrix&);
Matrix& GradientDescent(const Matrix&, const Matrix&, const Matrix&, double, int);

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
		double cost = ComputeCost(features, response, theta);
		outFile << "With theta = [0; 0], the cost is " << cost << std::endl;
		outFile << "The expected cost is approximately 32.07" << std::endl;

		Matrix theta2(2,1);
		theta2(0,0) = -1; theta2(1,0) = 2;
		outFile << "With theta = [-1; 2], the cost is " << ComputeCost(features, response, theta2) << std::endl;
		outFile << "The expected cost is approximately 54.24" << std::endl;

		outFile << "\nGradient descent..." << std::endl;
		double alpha = 0.01;
		int iterations = 1500;

// DEBUG DEBUG DEBUG DEBUG DEBUG //
		outFile << "DEBUG DEBUG DEBUG DEBUG DEBUG" << std::endl;
		Print(features, outFile);
		Print(response, outFile);
		Print(theta, outFile);
// DEBUG DEBUG DEBUG DEBUG DEBUG //



		theta = GradientDescent(features, response, theta, alpha, iterations);
		outFile << "Theta found by gradient descent:" << std::endl;
		Print(theta, outFile);
		outFile << "Expected theta values: [-3.6303; 1.1664]" << std::endl;

		status = 0;
	} catch (...) {
		std::cout << "FAILURE: Cannot complete Example1 Test!" << std::endl;
		outFile << "FAILURE: Cannot complete Example1 Test!" << std::endl;
		status = 1;
	}

	outFile.close();

	return status;
}

double ComputeCost(const Matrix& features, const Matrix& response, const Matrix& fitParameters) {
	int numberOfSamples = response.length();
	Matrix featuresFit = features * fitParameters;
	return pow((response - featuresFit).norm(), 2) / (2 * numberOfSamples);
}



Matrix& GradientDescent(const Matrix& featuresIn, const Matrix& response, const Matrix& fitParameters,
					   double alpha, int iterations) {
	Matrix features(featuresIn); // Must make a copy to get around the promise of constant yet still
								 // make a SubMatrix out of features.
	int numberOfSamples = response.length();
	Matrix& outParameters = *(new Matrix(fitParameters));
	for (int iter = 0; iter < iterations; ++iter) {
		Matrix error = (features * outParameters) - response; // difference between hypothesis and data)
		Matrix errorDerivativesHelper(numberOfSamples,2);
		errorDerivativesHelper(0,numberOfSamples-1,0,0) = error;
		// errorDerivativesHelper(0,numberOfSamples-1,0,0) = MatrixBuilder::ElementMultiply(features(0,numberOfSamples-1,0,0), error);
		// Pretty sure the first column of featrues is just a bunch of ones, so we can probably just
		// use error instead of element-wise multiplication.
		// I wish there was a better syntax to do this....
		errorDerivativesHelper(0,numberOfSamples-1,1,1) = MatrixBuilder::ElementMultiply(features(0,numberOfSamples-1,1,1), error);
		Matrix errorDerivatives = MatrixBuilder::Transpose(MatrixBuilder::SumReduce(errorDerivativesHelper, 1));
		outParameters = outParameters - ((alpha / numberOfSamples) * errorDerivatives);
	}

	return outParameters;
}

void Print(const Matrix& mat, ofstream& outFile) {
	outFile << mat << std::endl;
}

void Print(const SubMatrix& sm, ofstream& outFile) {
	outFile << sm << std::endl;
}



#include <iostream>

#include "Matrix.h"

int TestMatrix();

int main (int argc, char** argv) {

	std::cout << "Hello World!" << std::endl;

	int status = TestMatrix();

	return status;
}

int TestMatrix() {
	try{
		Matrix matOne;
		Matrix matTwo(2,2);
		Matrix matThree(matOne);

		matOne.setCols(12);
		matOne.setRows(3);

		Matrix matFour = matOne;

		std::cout << "Matrix 1: " << matOne << std::endl;
		std::cout << "Matrix 2: " << matTwo << std::endl;
		std::cout << "Matrix 3: " << matThree << std::endl;
		std::cout << "Matrix 4: " << matFour << std::endl;

		return 0;
	} catch (...) {
		std::cout << "Failed Matrix Test!" << std::endl;
		return 1;
	}
}

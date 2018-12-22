

#include <iostream>

#include "Matrix.h"

int TestMatrix();
void Print(const Matrix&, int);




int main (int argc, char** argv) {

	std::cout << "Hello World!" << std::endl;

	int status = TestMatrix();

	return status;
}







int TestMatrix() {
	try{
		Matrix mat1;
		Print(mat1, 1);

		Matrix mat2(2,2);
		Print(mat2, 2);

		Matrix mat3(mat1);
		Print(mat3, 3);

		mat1.setCols(12);
		mat1.setRows(3);
		Print(mat1, 1);

		Matrix mat4 = mat1;
		Print(mat4, 4);

		Matrix mat5(2,2,1.);
		Print(mat5, 5);

		Matrix mat6 = mat5;
		Print(mat6, 6);

		std::vector<std::vector<double>> vec1(9, vector<double>(2, -1.0));
		Matrix mat7(vec1);
		Print(mat7, 7);

		Matrix mat8 = vec1;
		Print(mat8, 8);

		mat4.setRows(9);
		mat4.setCols(2);
		mat4.setData(vec1);
		Print(mat4, 4);

		Matrix mat10(4,2);
		for (int i = 0; i < 4; ++i) {
			mat10.insert(i,0,i);
		}
		for (int i = 0; i < 4; ++i) {
			mat10.insert(i,1,10-i);
		}
		Print(mat10, 10);

		Matrix mat11(1,1);
		mat11.insert(0,0,mat10.extract(0,0));
		Print(mat11,11);

		return 0;
	} catch (...) {
		std::cout << "Failed Matrix Test!" << std::endl;
		return 1;
	}
}

void Print(const Matrix& m, int matrixNumber) {
	std::cout << "Matrix " << matrixNumber << ": " << m << std::endl;
}

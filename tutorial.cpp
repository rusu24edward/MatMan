

#include <iostream>

#include "Matrix.h"

int TestMatrix();
void Print(const Matrix&);




int main (int argc, char** argv) {

	std::cout << "Hello World!" << std::endl;

	int status = TestMatrix();
	return status;
}







int TestMatrix() {
	try{
		Matrix mat1;
		Print(mat1);

		Matrix mat2(2,2);
		mat2.setName("Matrix 2");
		Print(mat2);

		Matrix mat3(mat1);
		mat3.setName("Matrix 3");
		Print(mat3);

		Matrix mat4 = mat1;
		mat4.setName("Matrix 4");
		Print(mat4);

		Matrix mat5(2,2,1.);
		mat5.setName("Matrix 5");
		Print(mat5);

		Matrix mat6 = mat5;
		mat6.setName("Matrix 6");
		Print(mat6);

		std::vector<std::vector<double>> vec1(9, vector<double>(2, -1.0));
		Matrix mat7(vec1);
		mat7.setName("Matrix 7");
		Print(mat7);

		Matrix mat8 = vec1;
		mat8.setName("Matrix 8");
		Print(mat8);

		Matrix mat9(2,1);
		mat9.setName("Matrix 9");
		Print(mat9);

		Matrix mat10(4,2);
		mat10.setName("Matrix 10");
		for (int i = 0; i < 4; ++i) {
			mat10.insert(i,0,i);
		}
		for (int i = 0; i < 4; ++i) {
			mat10.insert(i,1,10-i);
		}
		Print(mat10);

		Matrix mat11(1,1);
		mat11.setName("Matrix 11");
		mat11.insert(0,0,mat10.extract(1,1));
		Print(mat11);

		mat2 = vec1;
		Print(mat2);

		std::vector<std::vector<double>> vec2;
		vec2.push_back(vector<double>(5));
		vec2.push_back(vector<double>(3));
		vec2.push_back(vector<double>(5));
		try {
			Matrix mat12(vec2);
			mat12.setName("Matrix 12");
		} catch (const char* msg) {
			std::cout << msg << std::endl;
		}

		return 0;
	} catch (...) {
		std::cout << "Failed Matrix Test!" << std::endl;
		return 1;
	}
}

void Print(const Matrix& m) {
	std::cout << m << std::endl;
}

all: tutorial.exe Example1.exe

Example1.exe: Example1.o NamedObject.o MatrixBase.o Matrix.o SubMatrix.o MatrixBuilder.o Reader.o
	g++ -o Example1.exe Example1.o NamedObject.o MatrixBase.o Matrix.o SubMatrix.o MatrixBuilder.o Reader.o

Example1.o: Example1.cpp
	g++ -c Example1.cpp

tutorial_modified.exe: tutorial.o NamedObject.o MatrixBase.o Matrix.o SubMatrix.o
	g++ -o tutorial.exe tutorial.o NamedObject.o MatrixBase.o Matrix.o SubMatrix.o

tutorial.exe: tutorial.o NamedObject.o MatrixBase.o Matrix.o SubMatrix.o MatrixBuilder.o Reader.o
	g++ -o tutorial.exe tutorial.o NamedObject.o MatrixBase.o Matrix.o SubMatrix.o MatrixBuilder.o Reader.o

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

Reader.o: Reader.cpp Reader.h
	g++ -c Reader.cpp

MatrixBuilder.o: MatrixBuilder.cpp MatrixBuilder.h
	g++ -c MatrixBuilder.cpp

SubMatrix.o: SubMatrix.cpp SubMatrix.h
	g++ -c SubMatrix.cpp

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

MatrixBase.o: MatrixBase.cpp MatrixBase.h
	g++ -c MatrixBase.cpp

NamedObject.o: NamedObject.cpp NamedObject.h
	g++ -c NamedObject.cpp

clean:
	rm -rf NamedObject.o MatrixBase.o Matrix.o SubMatrix.o MatrixBuilder.o Reader.o tutorial.o tutorial.exe Example1.o Example1.exe


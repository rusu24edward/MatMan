all: tutorial.exe

tutorial.exe: tutorial.o Matrix.o MyVector.o
	g++ -o tutorial.exe tutorial.o Matrix.o MyVector.o

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

MyVector.o: MyVector.cpp MyVector.h
	g++ -c MyVector.cpp

clean:
	rm -rf MyVector.o Matrix.o tutorial.o tutorial.exe


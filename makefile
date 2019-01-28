all: tutorial.exe

tutorial.exe: tutorial.o Matrix.o Vector.o SubVector.o
	g++ -o tutorial.exe tutorial.o Matrix.o Vector.o SubVector.o

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

Vector.o: Vector.cpp Vector.h
	g++ -c Vector.cpp

SubVector.o: SubVector.cpp SubVector.h
	g++ -c SubVector.cpp

clean:
	rm -rf SubVector.o Vector.o Matrix.o tutorial.o tutorial.exe


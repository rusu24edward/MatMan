all: tutorial.exe

tutorial.exe: tutorial.o NamedObject.o Vector.o SubVector.o Matrix.o SubMatrix.o
	g++ -o tutorial.exe tutorial.o NamedObject.o Vector.o SubVector.o Matrix.o SubMatrix.o

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

SubMatrix.o: SubMatrix.cpp SubMatrix.h
	g++ -c SubMatrix.cpp

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

SubVector.o: SubVector.cpp SubVector.h
	g++ -c SubVector.cpp

Vector.o: Vector.cpp Vector.h NamedObject.h
	g++ -c Vector.cpp

NamedObject.o: NamedObject.cpp NamedObject.h
	g++ -c NamedObject.cpp

clean:
	rm -rf NamedObject.o Vector.o SubVector.o Matrix.o SubMatrix.o tutorial.o tutorial.exe


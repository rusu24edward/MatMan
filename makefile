all: tutorial.exe

tutorial.exe: clean tutorial.o NamedObject.o Matrix.o SubMatrix.o Reader.o
	g++ -o tutorial.exe tutorial.o NamedObject.o Matrix.o SubMatrix.o Reader.o

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

Reader.o: Reader.cpp Reader.h
	g++ -c Reader.cpp

SubMatrix.o: SubMatrix.cpp SubMatrix.h
	g++ -c SubMatrix.cpp

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

NamedObject.o: NamedObject.cpp NamedObject.h
	g++ -c NamedObject.cpp

clean:
	rm -rf NamedObject.o Matrix.o SubMatrix.o Reader.o tutorial.o tutorial.exe


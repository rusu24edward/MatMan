all: tutorial.exe

tutorial.exe: tutorial.o Matrix.o
	g++ -o tutorial.exe tutorial.o Matrix.o

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

clean:
	rm -rf tutorial.o tutorial.exe


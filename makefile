all: tutorial.exe

tutorial.exe: tutorial.o
	g++ -o tutorial.exe tutorial.o

tutorial.o: tutorial.cpp Matrix.h
	g++ -c tutorial.cpp Matrix.h

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

clean:
	rm -rf MainUtils.o tutorial.o tutorial.exe


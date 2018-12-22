all: tutorial.exe

tutorial.exe: tutorial.o Matrix.h
	g++ -o tutorial.exe tutorial.o Matrix.h

tutorial.o: tutorial.cpp
	g++ -c tutorial.cpp

# Reader.o: Reader.cpp Reader.h
# 	g++ -I /usr/include/boost/numeric -c Reader.cpp

# MainUtils.o: MainUtils.cpp MainUtils.h Matrix.h
# 	g++ -c MainUtils.cpp Matrix.h

clean:
	rm -rf MainUtils.o tutorial.o tutorial.exe


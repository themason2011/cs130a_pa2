CXX=g++

CXXFLAGS= -std=c++11 -Wall -g

BINARIES=prog1.out

all: prog1.out

prog1.out: prog1.cpp
	g++ -o prog1.out prog1.cpp

clean:
	/bin/rm -f *.o ${BINARIES}
CXX=g++
CXXFLAGS= -std=c++11
prog: read.o
	$(CXX) -o prog read.o

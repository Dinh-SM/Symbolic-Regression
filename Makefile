CXXFLAGS= -Wall

test: main.cpp
	g++ -o test main.cpp
	./test
	rm test

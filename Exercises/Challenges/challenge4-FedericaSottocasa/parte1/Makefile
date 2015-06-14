CXX=clang++
CXXFLAGS=-Wall -std=c++11

main: main.cpp Polynomial.cpp
	$(CXX) $(CXXFLAGS) Polynomial.cpp -c -std=c++11  -I.
	$(CXX) $(CXXFLAGS) main.cpp -c -std=c++11  -I.
	$(CXX) $(CXXFLAGS) -o main  Polynomial.o main.o  -std=c++11


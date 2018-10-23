CXX = g++
CXXFLAGS = 
LDLIBS = -lcurl

main: main.o
	$(CXX) -o main main.o $(LDLIBS)
	
main.o: main.cpp
	$(CXX) -c main.cpp
	
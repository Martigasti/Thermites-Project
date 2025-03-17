CXX=g++
CXXFLAGS=-std=c++11 -Wall

all: grilles tests

EXEC_FILES= coord projet grille termite

coord.o : coord.cpp coord.hpp 
	$(CXX) $(CXXFLAGS) -c $<
    
grille.o : grille.cpp grille.hpp
	$(CXX) $(CXXFLAGS) -c $<

termite.o : termite.cpp termite.hpp
	$(CXX) $(CXXFLAGS) -c $<

projet.o : projet.cpp coord.hpp grille.hpp termite.hpp
	$(CXX) $(CXXFLAGS) -c $<
    
test.o : test.cpp coord.hpp grille.hpp termite.hpp
	$(CXX) $(CXXFLAGS) -c $<

grilles: projet.o coord.o grille.o termite.o
	$(CXX) -o $@ $^ 
	
tests: test.o coord.o grille.o termite.o
	$(CXX) -o $@ $^
    
clean:
	rm -f *.o $(EXEC_FILES)

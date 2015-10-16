CXX = g++ -std=c++11
CC = gcc -std=c99

all: permutation_enumerator random_graphs clique_partitions test

permutation_enumerator: permutation_enumerator.cpp
	$(CXX) -c permutation_enumerator.cpp

random_graphs: random_graphs.cpp
	$(CXX) -c random_graphs.cpp

clique_partitions: clique_partitions.cpp
	$(CXX) -c clique_partitions.cpp

test: permutation_enumerator random_graphs clique_partitions testy.cpp
	$(CXX) testy.cpp permutation_enumerator.o random_graphs.o clique_partitions.o -o testy

clean:
	rm *\~ testy *.o
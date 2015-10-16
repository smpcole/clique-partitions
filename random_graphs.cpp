#include "random_graphs.h"
#include <cstdlib>
#include <ctime>

namespace clique_partitions {

	bool **new_random_graph(const size_t n, const double p) {
		srand(time(NULL));
		bool **G = new bool*[n];
		for(size_t i = 0; i < n; i++) {
			G[i] = new bool[n];
			for(size_t j = 0; j < n; j++) {
				if(j == i)
					G[i][j] = false;
				else if(j > i)
					G[i][j] = rand() <= p * RAND_MAX;
				else
					G[i][j] = G[j][i];
			}
		}
		return G;
	}

	void delete_graph(bool **G, const size_t n) {
		for(size_t i = 0; i < n; i++) {
			delete[] G[i];
			G[i] = NULL;
		}
		delete[] G;
	}

	void print_graph(const bool *const*const G, const size_t n, std::ostream &out) {
		for(size_t i = 0; i < n; i++) {
			for(size_t j = 0; j < n; j++)
				out << (G[i][j] ? '1' : '0') << ' ';
			out << std::endl;
		}
	}
}

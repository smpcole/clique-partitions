#ifndef _RANDOM_GRAPHS_H
#define _RANDOM_GRAPHS_H

#include <cstddef>
#include <iostream>

namespace clique_partitions {
	
	bool **new_random_graph(const size_t n, const double p);

	void delete_graph(bool **G, const size_t n);

	void print_graph(const bool *const*const G, const size_t n, std::ostream &out = std::cout);

}

#endif

#ifndef _CLIQUE_PARTITIONS_H
#define _CLIQUE_PARTITIONS_H

#include <cstddef>

namespace clique_partitions {

	/*
	 * Return true iff. perm is an s-clique partition in G
	 */
	bool is_clique_partition(const int *const perm, const bool *const*const G, const size_t n, const size_t s);

	bool has_clique_partition(const bool *const*const G, const size_t n, const size_t s);

	unsigned int num_clique_partitions(const bool *const*const G, const size_t n, const size_t s);

	void test(const size_t s, const size_t k, const double p, const unsigned int num_graphs);

	unsigned int num_partitions(const size_t n, const size_t k);

}

#endif

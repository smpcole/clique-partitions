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

	/*
	 * Return number of partitions of [n] into parts of equal size s,
	 * where s is a function of n.
	 * 
	 * Will adjust n and s so that s is an integar and s divides n
	 *
	 * The argument and return types of s are double so that s matches most of the
	 * functions in math.h
	 */
	unsigned int num_partitions(const size_t n, double (*s)(double));

	double exp_num_clique_partitions(const size_t n, const size_t k, const double p);

	/* Return the expected number of s-clique partitions in G(n, p),
	 * where s is a function of n.
	 * 
	 * Will adjust n and s so that s is an integar and s divides n
	 *
	 * The argument and return types of s are double so that s matches most of the
	 * functions in math.h
	 */	 
	double exp_num_clique_partitions(const size_t n, double (*s)(double), const double p);

}

#endif

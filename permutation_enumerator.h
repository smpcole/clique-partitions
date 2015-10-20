#ifndef _PERMUTATION_ENUMERATOR_H
#define _PERMUTATION_ENUMERATOR_H

#include <cstddef>
#include <iostream>

namespace clique_partitions {

	class permutation_enumerator {
	private:
		void *pvt;
	public:
		
		permutation_enumerator(const size_t n, size_t *const a = NULL);
		~permutation_enumerator();
		
		/*
		 * Return true iff. have already enumerated all permutations of the array
		 */
		bool past_end();
		
		/*
		 * Return pointer to stored array
		 *
		 * If you get the pointer in this way you're not allowed to modify the array.
		 */
		const size_t *get_array();
		
		/*
		 * Increment array to next permutaion;
		 * for convenience, return a pointer to the array
		 */
		const size_t *next();
		
		void print_curr(std::ostream &out = std::cout);
	};

}

#endif

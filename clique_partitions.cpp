#include "clique_partitions.h"
#include "permutation_enumerator.h"
#include "random_graphs.h"
#include <cassert>

using namespace std;

namespace clique_partitions {

	inline unsigned long long factorial(const size_t n) {
		unsigned long long fact = 1;
		for(size_t i = 1; i <= n; i++)
			fact *= i;
		return fact;
	}

	unsigned long long num_partitions(const size_t n, const size_t k) {
		assert(!(n % k));
		size_t s = n / k;
		const unsigned long long sfact = factorial(s);
		unsigned long long N = factorial(n);
		for(size_t i = 1; i <= k; i++) {
			N /= i;
			N /= sfact;
		}			
		return N;
	}

	bool is_clique_partition(const size_t *const perm, const bool *const*const G, const size_t n, const size_t s) {
		assert(!(n % s));
		size_t start = 0;
		while(start < n) {
			for(size_t i = start; i < start + s; i++) {
				for(size_t j = i + 1; j < start + s; j++) {
					if(!G[perm[i]][perm[j]])
						return false;
				}
			}
			start += s;
		}
		return true;
	}

	bool has_clique_partition(const bool *const*const G, const size_t n, const size_t s) {
		assert(!(n % s));
		permutation_enumerator perms(n);
		while(!perms.past_end()) {
			if(is_clique_partition(perms.get_array(), G, n, s))
			   return true;
			perms.next();
		}
		return false;
	}

	unsigned long long num_clique_partitions(const bool *const*const G, const size_t n, const size_t s) {
		assert(!(n % s));
		unsigned long long N = 0;
		permutation_enumerator perms(n);
		while(!perms.past_end()) {
			if(is_clique_partition(perms.get_array(), G, n, s))
				N++;
			perms.next();
		}

		// We overcount each partition k!(s!)^k times
		const size_t k = n / s;
		unsigned long long sfact = factorial(s);
		assert(!(N % sfact));
		for(size_t i = 1; i <= k; i++) {
			assert(!(N % i));
			N /= i;
			N /= sfact;
		}
		return N;
	}

	unsigned long long num_partitions(const size_t n, double (*s)(double)) {
		const size_t ints = (*s)(n), k = n / ints;
		unsigned long long (*np)(const size_t, const size_t) = &num_partitions;
		return num_partitions(ints * k, k);
	}

	double exp_num_clique_partitions(const size_t n, const size_t k, const double p) {
		// Raise p^(n(n / k - 1) / 2)
		double prb = p;
		// pwr represents the power to which p has been raised
		unsigned long long pwr = 1, maxpwr = n * (n / k - 1) / 2;
		while(2 * pwr <= maxpwr) {
			prb *= prb;
			pwr *= 2;
		}
		while(pwr++ < maxpwr)
			prb *= p;
		return prb * num_partitions(n, k);		
	}

	double exp_num_clique_partitions(const size_t n, double (*s)(double), const double p) {
		const size_t ints = (*s)(n), k = n / ints;
		double (*cp)(const size_t, const size_t, const double) = &exp_num_clique_partitions;
		return (*cp)(ints * k, k, p);
	}

	void test(const size_t s, const size_t k, const double p, const unsigned short num_graphs) {
		unsigned long long totalNumPartitions, numWithPartitions;
		const size_t n = s * k;
		totalNumPartitions = numWithPartitions = 0;
		for(unsigned short i = 0; i < num_graphs; i++) {
			bool **G = new_random_graph(n, p);
			unsigned long long N = num_clique_partitions(G, n, s);
			totalNumPartitions += N;
			if(N)
				numWithPartitions++;
			delete_graph(G, n);
		}
		
		cout << "Avg. number of " << s << "-clique partitions: " << ((double)totalNumPartitions) / ((double)num_graphs) << " (" << num_partitions(n, k) << " possible)" << endl;
		cout << "Proportion of graphs with " << s << "-clique partitions: " << ((double)numWithPartitions) / ((double)num_graphs) << endl;
	}

}

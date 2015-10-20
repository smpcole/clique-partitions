#include "permutation_enumerator.h"

using namespace std;

namespace clique_partitions {

	struct pvt_data {
		size_t *const a;
		const size_t n;
		size_t i; // Keeps track of current index of nth element
		bool past_end;
		const bool owns_a;// True if a was allocated by this object
		permutation_enumerator *child;

		pvt_data(size_t *const nums, const size_t size, const bool owns_array) : 
			a(nums), 
			n(size), 
			child(size ? new permutation_enumerator(size - 1, a) : NULL),
			i(size - 1),
			past_end(!size),
			owns_a(owns_array) {
		}

		~pvt_data() {
			if(child != NULL)
				delete child;
			if(owns_a) {
				delete[] a;
				// cerr << "Deleted array" << endl;
			}
		}
	};

	const size_t *permutation_enumerator::get_array() {
		return ((pvt_data *)pvt)->a;
	}
	
	permutation_enumerator::permutation_enumerator(const size_t n, size_t *const a) {
		// If a == NULL, then we need to create a new array and delete it when we're done
		const bool own_array = (a == NULL);
		size_t *const newa = (own_array ? new size_t[n] : a);

		// Fill in newa with the numbers 0, ..., n - 1
		if(newa != a) {
			// cerr << "Created array" << endl;
			for(size_t i = 0; i < n; i++)
				newa[i] = i;
		}
			
		pvt = (void *)(new pvt_data(newa, n, own_array)); 
	}

	const size_t *permutation_enumerator::next() {
		
		if(!past_end()) {

			pvt_data *pvt = (pvt_data *)(this->pvt);

			// If nth element is not at the beginning of the list
			if(pvt->i) {
				// Move it down an index
				const size_t tmp = pvt->a[pvt->i];
				pvt->a[pvt->i] = pvt->a[pvt->i - 1];
				pvt->i -= 1;
				pvt->a[pvt->i] = tmp;
			}
			else {

				// Move nth element back to end
				const size_t tmp = pvt->a[0];
				for(size_t i = 0; i < pvt->n - 1; i++)
					pvt->a[i] = pvt->a[i + 1];
				pvt->a[pvt->n - 1] = tmp;
				pvt->i = pvt->n - 1;

				if(pvt->child != NULL) {
					pvt->child->next();
					if(pvt->child->past_end()) {
						pvt->past_end = true;
						delete pvt->child;
						pvt->child = NULL;
					}
				}
				else
					pvt->past_end = true;
			}
		}

		return get_array();
	}

	bool permutation_enumerator::past_end() {
		return ((pvt_data *)pvt)->past_end;
	}

	void permutation_enumerator::print_curr(ostream &out) {
		pvt_data *pvt = (pvt_data *)(this->pvt);
		for(size_t i = 0; i < pvt->n; i++)
			out << pvt->a[i];
		out << endl;
	}

	permutation_enumerator::~permutation_enumerator() {
		delete (pvt_data *)pvt;
		pvt = NULL;
	}

}

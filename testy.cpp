#include <iostream>
#include "permutation_enumerator.h"
#include "random_graphs.h"
#include "clique_partitions.h"

using namespace std;
using namespace clique_partitions;

int main(int argc, char *argv[]) {

	size_t n = atoi(argv[1]);

	unsigned int N = 0;
	permutation_enumerator perms(n);
	while(!perms.past_end()) {
		cout << "Permutation " << ++N << ": ";
		perms.print_curr();
		perms.next();
	}

 	cout << "Enumerated " << N << " permutation" << (N == 1 ? "" : "s") << endl;

	bool **G = new_random_graph(10, .9);
	print_graph(G, 10);
	if(has_clique_partition(G, 10, 5))
		cout << "Happy" << endl;
	else
		cout << "Sad" << endl;
	N = num_clique_partitions(G, 10, 5);
	cout << N << " 5-clique partitions found" << endl;
	delete_graph(G, 10);

	test(8, 2, .5, 20);
	return 0;
}

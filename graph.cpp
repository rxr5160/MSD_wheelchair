/**
* IN .H FILE
* this should just be merges with traversal once figured out
*
* node data type
* for graph creating map
*
**/

#include <iostream>
using namespace std;

// intersection nodes
// relate distance to neighbors
typedef struct g_node {
	char[12] name;
	struct *g_node[4] neighbors;
	int[4] distance;
} node;
//I know theres a better way to do the adjacency list 
//  but brain small and this *does* work




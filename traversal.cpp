/**
* graph traversal
**/

#include <iostream>
using namespace std;
#include "graph.h"



char* closest (graph* g) {
	int closest_distance = 256;
	char[16] closest_name = "";
	for (int i=0; i<4; i++) {
		if (g->distance[i] < closest_distance) {
			closest_distance = g->distance[i];
			closest_name = g->neighbors[i];
		}
	}
	return closest_name;
}





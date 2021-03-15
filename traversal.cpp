/**
* graph traversal
**/

#include <iostream>
#include <climits>
using namespace std;
#include "traversal.h"
#include "graph.h"


/**
function Dijkstra(Graph, source):
       dist[source]  := 0                     // Distance from source to source is set to 0
       for each vertex v in Graph:            // Initializations
           if v ≠ source
               dist[v]  := infinity           // Unknown distance function from source to each node set to infinity
           add v to Q                         // All nodes initially in Q

      while Q is not empty:                  // The main loop
          v := vertex in Q with min dist[v]  // In the first run-through, this vertex is the source node
          remove v from Q

          for each neighbor u of v:           // where neighbor u has not yet been removed from Q.
              alt := dist[v] + length(v, u)
              if alt < dist[u]:               // A shorter path to u has been found
                  dist[u]  := alt            // Update distance of u

      return dist[]
  end function
*/

int* path (vector<pair<int,int> > *adj, int startPoint, int endPoint) {
	//path array
	int *p = new int[MAXNODES];
	p[0] = startPoint;

	//create distance array
	//int dist[MAXNODES] = {INT_MAX};
	//dist[startPoint] = 0; //distance from start to start is zero

	//visited array
	int visited[MAXNODES] = {0};
    //visited[0] = 1;

    if(startPoint == endPoint){
        return p;
    }

/**
 FOR NOW ASSUME START AT NODE 0
**/
	//for each node in graph
	int pathPoint = 0; //increments before any changes are made for zero still skips the zero start index
	//for (int u=0; u<MAXNODES; u++) {
    int u = 0;
    while(1) {
        if (u == endPoint) {
			//include end node
            pathPoint++;
			p[pathPoint] = endPoint;
			return p;
		}

		//if (u != startPoint && visited[u]!=1) { //skip zero for now
		if (visited[u]!=1) { //skip zero for now
			int minDist = INT_MAX;
			int minNode;
			pathPoint++;
			for (auto it = adj[u].begin(); it!=adj[u].end(); it++) {
                if (visited[it->first] == 0) {
				//dist[it->first] = it->second; //assign distance to array -> ??? huh
                    if (minDist > it->second) {
                        minDist = it->second;
                        minNode = it->first;
                    }
                }
			}
			p[pathPoint] = minNode;
			visited[u] = 1;
            if (u == minNode){
                break;
              }
            u = minNode;
		}
        else {
            u++;
        }
	}
	return p;
}





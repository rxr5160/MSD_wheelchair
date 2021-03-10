// C++ program to represent undirected and weighted graph
// using STL. The program basically prints adjacency list
// representation of graph
#include <bits/stdc++.h>
using namespace std;
#include "traversal.h"
#include "graph.h"

string LocationNames[] = {
    "BRINKMAN",
    "XEROX",
    "ENGHALL",
    "MECEOFFICE",
    "ROOM2340"
};

// To add an edge
void addEdge(vector <pair<int, int> > *adj, int u,
									int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt));
}

// Print adjacency list representaion ot graph
void printGraph(vector<pair<int,int> > adj[], int V)
{
	int v, w;
	for (int u = 0; u < V; u++)
	{
		cout << "Node " << LocationNames[u] << " makes an edge with \n";
		for (auto it = adj[u].begin(); it!=adj[u].end(); it++)
		{
			v = it->first;
			w = it->second;
			cout << "\tNode " << LocationNames[v] << " with edge weight ="
				<< w << "\n";
		}
		cout << "\n";
	}
}

// Driver code
vector<pair<int, int> >* create_node_list()
{
	int V = 5; //number of nodes
	vector<pair<int, int> > *adj = (vector<pair<int, int> > *) malloc(sizeof(vector<pair<int, int> >)*V);
	// addEdge(list, node, adjacent_node, weight)
    addEdge(adj, BRINKMAN, XEROX, 10);
    addEdge(adj, BRINKMAN, ROOM2340, 20);
    addEdge(adj, XEROX, ENGHALL, 30);
    addEdge(adj, XEROX, MECEOFFICE, 40);
    addEdge(adj, XEROX, ROOM2340, 50);
    addEdge(adj, ENGHALL, MECEOFFICE, 60);
    addEdge(adj, MECEOFFICE, ROOM2340, 70);
	printGraph(adj, V);

    return adj;
}

int main(){
	vector<pair<int,int> >* adj = create_node_list();
	int *p = path(adj, 0, 3);
	for (int x=0; x < 5; x++) {
		std::cout << p[x] << ", ";
	}
	std::cout <<"\n";
	delete[] p;
    free(adj);
}




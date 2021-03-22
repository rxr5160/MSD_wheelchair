/************************************************************************/
/* $Id: MainP.cpp 65 2010-09-08 06:48:36Z yan.qi.asu $                                                                 */
/************************************************************************/

#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "GraphElements.h"
#include "Graph.h"
#include "DijkstraShortestPathAlg.h"
//#include "YenTopKShortestPathsAlg.h"

using namespace std;


void testDijkstraGraph()
{
	Graph* my_graph_pt = new Graph("map_v2");
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex(0), my_graph_pt->get_vertex(6));
	result->PrintOut(cout);
//
/**
 * gives each vertex and cumulative weight
 *
	cout << result->GetVertex(0)->getID();
	cout << result->GetVertex(0)->Weight();
	cout << "\n";	
	cout << result->GetVertex(1)->getID();
	cout << result->GetVertex(1)->Weight();
	cout << "\n";	
	cout << result->GetVertex(2)->getID();
	cout << result->GetVertex(2)->Weight();
	cout << "\n";	
	cout << result->GetVertex(3)->getID();
	cout << result->GetVertex(3)->Weight();
	cout << "\n";	
*/


}

/*void testYenAlg()
{
	Graph my_graph("test_1");

	YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex(0),
		my_graph.get_vertex(5));

	int i=0;
	while(yenAlg.has_next())
	{
		++i;
		yenAlg.next()->PrintOut(cout);
	}
}*/

int main(void)
{
	cout << "Welcome to the real world!" << endl;

	testDijkstraGraph();
	//testYenAlg();
}

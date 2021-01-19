#include <vector>
#include <set>

#include "misc.h"

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
/**
 * @brief      Graph class. All the graph based calculations will take place here
 */
class Graph
{
	public:
		Graph();
		void addEdge(char, char, int);
		string computeSingleShortestPath(char, char, int);
		string printMinPath(vector<int>, int, int);
		void printGraph();

	private:
		int getVertexIndex(char);
		char getVertexFromIndex(int);
		int getVertCount();

		// Mapping from letter to vertex(used in graph construction) and vertex to letter(used for printing paths)
		vector<int> created; 		// To check if vertex has already been created or not
		// Adjaceny list: implemented as a map: <Src Label> -> [ (<Dest Label, Weight>) ]			
		ADJ_LIST list;

		// Set of edges for bookkeeping purposes
		set< pair<char, char> > edges;
		

};

#endif
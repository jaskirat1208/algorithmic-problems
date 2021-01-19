#include <bits/stdc++.h>

#include "graph.h"
#include "misc.h"

using namespace std;

/**
 * @brief      Constructs a new instance of a graph
 */
Graph::Graph() {
	for(int i = 0; i < N_LETTERS_IN_ALPHABET; i++) {
		this->created.push_back(0);
		ADJ_LIST_ELT v;
		this->list.push_back(v);
	}
}


/**
 * @brief      Gets the no of vertices
 *
 * @return     No of vertices.
 */
int Graph::getVertCount() {
	int nVertices = 0;
	for (int i = 0; i < created.size(); ++i)
	{
		nVertices+=created[i];
	}
	return nVertices;
}

/**
 * @brief      Gets the vertex index.
 *
 * @param[in]  v     vertex label
 */
int Graph::getVertexIndex(char v) {
	return (v - 'A');
}

/**
 * @brief      Gets the vertex from index.
 *
 * @param[in]  idx   The index
 *
 * @return     The vertex char.
 */
char Graph::getVertexFromIndex(int idx) {
	return (idx + 'A');
}

/**
 * @brief      Adds an edge the graph
 *
 * @param[in]  src     The source
 * @param[in]  dest    The destination
 * @param[in]  length  The length
 */
void Graph::addEdge(char src, char dest, int length) {
	int src_vertex_idx = this->getVertexIndex(src);
	int dest_vertex_idx = this->getVertexIndex(dest);

	// Mark as created: Needed for validation checks
	this->created[src_vertex_idx] = 1;
	this->created[dest_vertex_idx] = 1;

	this->list[src_vertex_idx].push_back(make_pair(dest_vertex_idx, length));
	this->list[dest_vertex_idx].push_back(make_pair(src_vertex_idx, length));

	// Push both forward and reverse in the record book to make sure no other back edges are present 
	I_PAIR edge_pair = make_pair(src, dest), rev_edge_pair = make_pair(dest, src);

	// Self look or back edge present => throw Logical input Error
	if (this->edges.find(edge_pair) != this->edges.end() || src == dest)
		throw ErrorCodes::LogicalInputErrorCode;

	// Insert the edge into edges list for bookkeeping
	this->edges.insert(edge_pair);
	this->edges.insert(rev_edge_pair);
}

/**
 * @brief      Prints a graph.
 */
void Graph::printGraph() {
	for (int i = 0; i < this->list.size(); ++i)
	{
		cout<<"Vertex "<<i<<": ";
		for (int j = 0; j < this->list[i].size(); ++j)
		{
			cout<<this->list[i][j].first<<" "<<this->list[i][j].second<<", ";
		}
		cout<<endl;
	}
}

/**
 * @brief      Calculates the single shortest path in the graph.
 *
 * @param[in]  src   The source
 * @param[in]  dest  The destination
 *
 * @return     The single shortest path.
 */
string Graph::computeSingleShortestPath(char src, char dest, int max_len) {
	int nVertices = this->getVertCount();
	int src_vertex_idx = this->getVertexIndex(src);
	int dest_vertex_idx = this->getVertexIndex(dest);

	if (!this->created[src_vertex_idx] || !this->created[dest_vertex_idx])
	{
		throw ErrorCodes::LogicalInputErrorCode;
	}
	
	// Create a min heap of format (dist, vertex) showing all elements NOT in the special set 
	priority_queue< I_PAIR, vector <I_PAIR> , greater<I_PAIR> > min_heap;
	
	vector<int> distances(N_LETTERS_IN_ALPHABET, INT_MAX);		
	vector<int> previous(N_LETTERS_IN_ALPHABET, 0);				// To track the path
	vector<int> nPaths(N_LETTERS_IN_ALPHABET, 1);				// No of paths

	// Push src into the min_heap
	min_heap.push(make_pair(0, src_vertex_idx )); 
	distances[src_vertex_idx] = 0;					// Update distance of source = 0

	while(!min_heap.empty()) {
		// Closest number
		int closest_vertex = min_heap.top().second;
		min_heap.pop();

		// Look into the adjacency list of closest vertex
		for (int i = 0; i < this->list[closest_vertex].size(); ++i)
		{
			// Update the distances of ever vertex within to dist[closest_vertex] + weight of edge
			I_PAIR edge = this->list[closest_vertex][i];

			int prev_dist = distances[closest_vertex]; 
			int edge_weight = edge.second;
			int edge_endpt = edge.first;
			int current_dist = distances[edge_endpt];

			if (current_dist > prev_dist + edge_weight)
			{
				// Update the minimum distance
				distances[edge_endpt] = prev_dist + edge_weight;
				previous[edge_endpt] = closest_vertex;
				nPaths[edge_endpt] = nPaths[closest_vertex];
				min_heap.push(make_pair(distances[edge_endpt], edge_endpt));
			}
			else if(current_dist == prev_dist + edge_weight) {
				nPaths[edge_endpt]++;
			}
		}
	}
	
	// The desired path could not be found
	if (distances[dest_vertex_idx] > max_len)
	{
		throw ErrorCodes::FailedToFindPathCode;
	}
	if(nPaths[dest_vertex_idx] > 1 ) {
		throw ErrorCodes::LogicalInputErrorCode;
	}
	// Check if graph is disconnected from the distances array
	for (int i = 0; i < N_LETTERS_IN_ALPHABET; ++i)
	{
		if (distances[i] == INT_MAX && this->created[i] == 1)
		{
			throw ErrorCodes::LogicalInputErrorCode;
		}	
	}	
	// Print the minimum path from previous array
	return this->printMinPath(previous, dest_vertex_idx, src_vertex_idx);
}

string Graph::printMinPath(vector<int> previous, int curr_node, int src_node) {
	if (curr_node == src_node)
	{
		return getString(this->getVertexFromIndex(curr_node));
	}

	string path_str = printMinPath(previous, previous[curr_node], src_node) + "->" + getString(this->getVertexFromIndex(curr_node)); 
	return path_str;
}

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define N_LETTERS_IN_ALPHABET 26
#define ADJ_LIST_ELT vector< pair<int, int> >
#define ADJ_LIST vector< ADJ_LIST_ELT >

using namespace std;

/**
 * A generic representation of a path from `src`->`dest` with length `length`
 * Also used for parsing edges with `length` as weight of the edge 
 */
typedef struct Path
{
	char src;
	char dest;
	int length;
} Path;


/**
 * Error codes:
 * - Syntax error
 * - Logical input error:
 * 		- Duplicate edge definition
 * 		- Specifying start end that is not defined in a graph
 * 		- Disconnected graph
 * 		- More than one shortest path found
 */
enum class ErrorCodes {
	InputSyntaxErrorCode,
	LogicalInputErrorCode,
	FailedToFindPathCode	
};

/**
 * @brief      Graph class. All the graph based calculations will take place here
 */
class Graph
{
	public:
		Graph();
		void addEdge(char, char, int);
		void computeSingleShortestPath(char, char);
		void printPath();
		void printGraph();

	private:		
		// Mapping from letter to vertex(used in graph construction) and vertex to letter(used for printing paths)
		vector<char> path;			//
		vector<int> created; 		// To check if vertex has already been created or not
		// Adjaceny list: implemented as a map: <Src Label> -> [ (<Dest Label, Weight>) ]			
		ADJ_LIST list;

		int getVertexIndex(char u);
};

/**
 * @brief      Constructs a new instance of a graph
 */
Graph::Graph() {
	for(int i = 0; i < N_LETTERS_IN_ALPHABET; i++) {
		created.push_back(0);
		ADJ_LIST_ELT v;
		list.push_back(v);
	}
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
 * @brief      Adds an edge the graph
 *
 * @param[in]  src     The source
 * @param[in]  dest    The destination
 * @param[in]  length  The length
 */
void Graph::addEdge(char src, char dest, int length) {
	int src_vertex_idx = this->getVertexIndex(src);
	int dest_vertex_idx = this->getVertexIndex(dest);

	this->list[src_vertex_idx].push_back(make_pair(dest_vertex_idx, length));
	this->list[dest_vertex_idx].push_back(make_pair(src_vertex_idx, length));

	cout<<src_vertex_idx<<" "<<dest_vertex_idx<<endl;
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
 * @brief      Parsing the input
 */
class InputParser
{
	public:
		InputParser(string, string);
		Graph createGraph();
		Path getPathParams();

	private:
		string line1, line2;
		Path parseEdgeStr(string);
};

/**
 * @brief      Constructs a new InputParser
 *
 * @param[in]  line1  The line 1 of input
 * @param[in]  line2  The line 2 of input
 */
InputParser::InputParser(string line1, string line2) {
	this->line1 = line1;
	this->line2 = line2;
}

Path InputParser::parseEdgeStr(string edge) {
	stringstream ss(edge), patterns;
	char src='x', dest='y', pattern;
	int weight = 0;

	// Putting all the patterns together and comparing them with the expected pattern
	ss>>pattern>>src;						// '[', <source:char>
	patterns<<pattern;									// patterns: '['
	ss>>pattern>>dest;						// ',', <dest:char>
	patterns<<pattern;									// patterns: '[,'
	ss>>pattern>>weight;					// ',', <weight: int> 
	patterns<<pattern;									// patterns: '[,,'
	ss>>pattern;							// ']'
	patterns<<pattern;									// patterns: '[,,]'		

	if (patterns.str() != "[,,]" || !isupper(src) || !isupper(dest))
	{
		throw ErrorCodes::InputSyntaxErrorCode;
	}

	// Path p;
	// p.src = src;
	// p.dest = dest;
	// p.length = weight;
	
	return {
		src, dest, weight
	};	 
}

/**
 * @brief      Creates a graph from the first line of user input.
 */
Graph InputParser::createGraph() {
	stringstream ss(line1);
	string edge;
	Graph g = Graph();

	while(ss>>edge) {
		Path p = this->parseEdgeStr(edge);
		g.addEdge(p.src, p.dest, p.length);
	}

	g.printGraph();
	return g;
}

/**
 * @brief      Gets the path parameters.
 *
 * @return     The path parameters.
 */
Path InputParser::getPathParams() {
	stringstream ss(this->line2), patterns;
	char src, dest, pattern;
	int max_len;
	
	// Parse the source vertex
	ss>>src;

	// Parse pattern ->
	ss>>pattern;
	patterns<<pattern;
	ss>>pattern;
	patterns<<pattern;

	// Parse the destination vertex
	ss>>dest;
	// Parse a ','
	ss>>pattern;
	patterns<<pattern;

	if (patterns.str() != "->," || !isupper(src) || !isupper(dest))
	{
		throw ErrorCodes::InputSyntaxErrorCode;
	}
	
	ss>>max_len;

	return {
		src, dest, max_len
	};
}

/**
 * @brief      Handling exceptions
 *
 * @param[in]  err_code  The error code
 */
void handleExceptions(ErrorCodes err_code) {
	switch(err_code) {
		case ErrorCodes::InputSyntaxErrorCode: 
			cout<<"E1"<<endl;
			break;
		case ErrorCodes::LogicalInputErrorCode: 
			cout<<"E2"<<endl;
			break;
		case ErrorCodes::FailedToFindPathCode: 
			cout<<"E3"<<endl;
			break;
		default: 
			throw "Unsupported Exception";
	}
}

/**
 * @brief      Driver program
 */
int main() {
	try {
		string line1, line2;
		getline(cin, line1);
		getline(cin, line2);
		InputParser parser(line1, line2);
		parser.createGraph();
		Path p = parser.getPathParams();
		cout<<p.src<<" "<<p.dest<<" "<<p.length;
		// graph.computeSingleShortestPath(u, v);

		// throw ErrorCodes::InputSyntaxErrorCode;
	}
	catch(ErrorCodes err_code) {
		handleExceptions(err_code);
	}

    return 0;
}
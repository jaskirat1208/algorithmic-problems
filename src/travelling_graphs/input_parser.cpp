#include <bits/stdc++.h>

#include "input_parser.h"
#include "graph.h"
#include "misc.h"

using namespace std;

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

/**
 * @brief      Parsing the edge
 *
 * @param[in]  edge  The edge string
 *
 * @return     Separated components of the edge: source, destination and weight
 */
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

	// g.printGraph();
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

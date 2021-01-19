#include <string>

#include "graph.h"
#include "misc.h"

#ifndef INPUTPARSER_H
#define INPUTPARSER_H

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

#endif
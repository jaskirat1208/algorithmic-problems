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

#include "input_parser.h"
#include "graph.h"
#include "misc.h"

using namespace std;


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
		Graph g = parser.createGraph();
		Path p = parser.getPathParams();

		string shortest_path = g.computeSingleShortestPath(p.src, p.dest, p.length);
		cout<<shortest_path<<endl;
	}
	catch(ErrorCodes err_code) {
		handleExceptions(err_code);
	}

    return 0;
}
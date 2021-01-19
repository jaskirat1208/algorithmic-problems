#include <string>

using namespace std;

#define N_LETTERS_IN_ALPHABET 26
#define I_PAIR pair<int, int>
#define ADJ_LIST_ELT vector< I_PAIR >
#define ADJ_LIST vector< ADJ_LIST_ELT >

#ifndef MISC_H
#define MISC_H

/**
 * @brief      Converts a single char to string
 *
 * @param[in]  x     char
 *
 * @return     One char string.
 */
static string getString(char x) 
{ 
    string s(1, x); 
  
    return s;    
} 

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
 * 		- Duplicate edge definition									-- check
 * 		- Specifying start end that is not defined in a graph		-- check
 * 		- Disconnected graph										-- TBI
 * 		- More than one shortest path found							-- check
 */
enum class ErrorCodes {
	InputSyntaxErrorCode,
	LogicalInputErrorCode,
	FailedToFindPathCode	
};

#endif
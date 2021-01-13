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

using namespace std;

struct Date
{
    int Day;
    int Year;
    int Month;
};

/**
 * @brief      Overloading operator < for comparing two dates
 *
 * @param[in]  lhs   The left hand side
 * @param[in]  rhs   The right hand side
 *
 * @return     The result of the less-than comparison
 */
inline bool operator< (const Date& lhs, const Date& rhs) {
	if (lhs.Year != rhs.Year)
		return lhs.Year < rhs.Year;

	if (lhs.Month != rhs.Month)
		return lhs.Month < rhs.Month;

	if(lhs.Day != rhs.Day)
		return lhs.Day < rhs.Day;

	return 0;
}

/**
 * @brief      Greater-than comparison operator for dates.
 *
 * @param[in]  lhs   The left hand side
 * @param[in]  rhs   The right hand side
 *
 * @return     The result of the greater-than comparison
 */
inline bool operator> (const Date& lhs, const Date& rhs) { 
	// lhs > rhs <=> rhs < lhs
	return rhs < lhs; 
}

/**
 * @brief      Less-than-or-equal comparison operator for dates.
 *
 * @param[in]  lhs   The left hand side
 * @param[in]  rhs   The right hand side
 *
 * @return     The result of the less-than-or-equal comparison
 */
inline bool operator<=(const Date& lhs, const Date& rhs) { 
	// Not greater than
	return !(lhs > rhs); 
}

/**
 * @brief      Greater-than-or-equal comparison operator for dates.
 *
 * @param[in]  lhs   The left hand side
 * @param[in]  rhs   The right hand side
 *
 * @return     The result of the greater-than-or-equal comparison
 */
inline bool operator>=(const Date& lhs, const Date& rhs) { 
	// Not less than
	return !(lhs < rhs); 
}

/**
 * @brief      Equality operator.
 *
 * @param[in]  lhs   The left hand side
 * @param[in]  rhs   The right hand side
 *
 * @return     The result of the equality
 */
inline bool operator== (const Date&lhs, const Date& rhs) {
	// Less than or equal to but not less than
	return !(lhs < rhs) && (lhs <= rhs);
}

/*
 * Complete the function below.
 */
Date ThirdLatest(std::vector<Date> & dates) {
	Date max1 = {0, 0, 0}, max2 = {0, 0, 0}, max3 = {0, 0, 0};

	for (int i = 0; i < dates.size(); ++i) {
		// Compare date with max date
		if (dates[i] >= max1) {
			// If date == max date, ignore the date and move on
			if(dates[i] == max1)
				continue;
			// If date > max1: update max3 = max2, max2 = max1, max1 = date
			max3 = max2;
			max2 = max1;
			max1 = dates[i];
		}
		else {
			if (dates[i] >= max2) {
				// If date == max2: ignore and move on
				if(max2 == dates[i])
					continue;
				// If max1 > date > max2: update max3 = max2 and max2 = date
			 	max3 = max2;
			 	max2 = dates[i];
			} 
			else {
				if (dates[i] > max3) {
					// If max2 > date > max3: update max3 = date
					max3 = dates[i];
				}
			}
		}
	}

	return max3;
}

int main() {
    int numberOfEntries;
    int res = scanf("%d\n", &numberOfEntries);
    std::vector<Date> dates;
    for (int i = 0; i < numberOfEntries; ++i)
    {
        Date date;
        res = scanf("%d-%d-%d", &date.Day, &date.Month, &date.Year);
        dates.push_back(date);
    }    
    
    Date result = ThirdLatest(dates);
    printf("%02d-%02d-%d\n", result.Day, result.Month, result.Year);
    return 0;
}
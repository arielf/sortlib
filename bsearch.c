#include "bsearch.h"

/*
 *  index_t  binsearch (a, lower, upper, key)
 *  KEY_T	a[];
 *  index_t	lower, upper;
 *  KEY_T	key;
 *
 *  Simple binary search:
 *
 *  Return (nonnegative) index of 'key' in array 'a[]' of KEY_T type.
 *  ['lower' .. 'upper'] is the range in which searching is performed.
 *  if 'key' was found, its index in 'a[]' (a nonnegative integer) is returned.
 *  -1 is returned if 'key' not found.
 *  -2 is returned if lower > upper on call.
 *
 *  Preconditions:
 *	lower <= upper and both are nonnegative integers.
 *	a[lower..upper] must be sorted.
 *
 *  (C) Copyright by Ariel Faigon,
 *  Released under the GNU GPL (General Public License) version 2
 *  or any later version (http://www.gnu.org/licenses/licenses.html)
 */
index_t binsearch (a, lower, upper, key)
KEY_T	a[];		/* array of values   */
index_t	lower, upper;	/* limit indices     */
KEY_T	key;		/* key value to search for */
{
	index_t	mid;	/* index of middle of range */

	if (lower > upper || lower < 0)	/* wrong call */
		return -2;

	while (lower <= upper) {
		mid = (lower + upper) / 2;
		if (a[mid] < key)
			lower = mid + 1;
		else if (a[mid] > key)
			upper = mid - 1;
		else		/* (a[mid] == key) -> found it */
			return mid;
	}

	return -1;	/* not found */
}


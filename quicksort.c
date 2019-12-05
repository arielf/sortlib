/*
 *  A library of sorting functions
 *
 *  Written by:  Ariel Faigon,  1987
 *
 *  (C) Copyright by Ariel Faigon, 1996
 *  Released under the GNU GPL (General Public License) version 2
 *  or any later version (http://www.gnu.org/licenses/licenses.html)
 */
#include	<stdio.h>
#include	"sort.h"

/*------------------------------------------------------------------- 
 *		  This file shouldn't be touched.
 *	     For customizable parameters, see 'sort.h'
 *-----------------------------------------------------------------*/

/*
 |  void  quicksort (array, lower, upper)
 |  KEY_T  array[];
 |  int    lower, upper;
 |
 |  Abstract:	Sort array[lower..upper] into increasing order.
 |
 |  Method:	C. A. R. Hoare's Quick-sort (ala Jon Bentley)
 */

void  quicksort (array, lower, upper)
register KEY_T  array[];
register int    lower, upper;
{
	register int	i, m;
	register KEY_T	temp, pivot;

	if (lower < upper) {
		SWAP(array[lower], array[(upper+lower)/2]);
		pivot = array[lower];
		m = lower;
		for (i = lower + 1; i <= upper; i++)
			if (LT(array[i], pivot)) {
				m++;
				SWAP(array[m], array[i]);
			}
		SWAP(array[lower], array[m]);
		quicksort (array, lower, m - 1);
		quicksort (array, m + 1, upper);
	}
}


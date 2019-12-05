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
 |  void  quickersort (array, lower, upper)
 |  KEY_T  array[];
 |  int    lower, upper;
 |
 |  Abstract:	Sort array[lower..upper] into increasing order.
 |
 |  Method:	Quicker sort using a sentinel (ala Robert Sedgewick)
 |
 |  BIG NOTE:
 |  Precondition: array[upper+1] must hold the maximum possible key.
 |  It is used as a sentinel, for this algorithm to work correctly.
 */

void  quickersort (array, lower, upper)
register KEY_T  array[];
register int    lower, upper;
{
    register int	i, j;
    register KEY_T	temp, pivot;

    if (lower < upper) {
	SWAP(array[lower], array[(upper+lower)/2]);
	i = lower;  j = upper + 1;  pivot = array[lower];
	while (1) {
	    /*
	     * ------------------------- NOTE --------------------------
	     * ignoring BIG NOTE above may lead to an infinite loop here
	     * ---------------------------------------------------------
	     */
	    do i++; while (LT(array[i], pivot));
	    do j--; while (GT(array[j], pivot));
	    if (j < i) break;
	    SWAP(array[i], array[j]);
	}
	SWAP(array[lower], array[j]);
	quickersort (array, lower, j - 1);
	quickersort (array, i, upper);
    }
}

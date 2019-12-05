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


/* Interesting tidbit:
 *
 * 15 has been found empirically as the optimal cutoff value in 1996
 *
 * 10 years later, in 2006, with computers being very different and
 * much faster, I revisited this constant and found the optimal value
 * to be a close tie between 15 and 16
 *
 * ~7 years later (end of 2013), on an Intel i7-4771 with hyper-threading,
 * larger caches, and a newer compiler (clang replacing gcc), technology
 * has finally made a difference and could make the switch to a higher
 * CUTOFF value.
 *
 * Here are the run times sorting a 100k element array:
 *  -DCUTOFF=10:    sedgesort:      5148 microsec.
 *  -DCUTOFF=15:    sedgesort:      5032 microsec.
 *  -DCUTOFF=16:    sedgesort:      4998 microsec.
 *  -DCUTOFF=20:    sedgesort:      4926 microsec.
 *  -DCUTOFF=25:    sedgesort:      4880 microsec.
 *  -DCUTOFF=30:    sedgesort:      4830 microsec.
 *  -DCUTOFF=50:    sedgesort:      4746 microsec. (minima)
 *  -DCUTOFF=60:    sedgesort:      4770 microsec.
 */
#ifndef CUTOFF
#  define CUTOFF 50
#endif

/*
 |  void  partial_quickersort (array, lower, upper)
 |  KEY_T  array[];
 |  int    lower, upper;
 |
 |  Abstract:
 |	Sort array[lower..upper] into a partial order
 |     	leaving segments which are CUTOFF elements long
 |     	unsorted internally.
 |
 |  Efficiency:
 |	Could be made faster for _worst_ cases by selecting
 |	a pivot using median-of-3. I don't do it because
 |	in practical cases my pivot selection is arbitrary and
 |	thus pretty random, your mileage may vary.
 |
 |  Method:
 |	Partial Quicker-sort using a sentinel (ala Robert Sedgewick)
 |
 |  BIG NOTE:
 |	Precondition: array[upper+1] holds the maximum possible key.
 |	with a cutoff value of CUTOFF.
 */

void  partial_quickersort (array, lower, upper)
register KEY_T  array[];
register int    lower, upper;
{
    register int	i, j;
    register KEY_T	temp, pivot;

    if (upper - lower > CUTOFF) {
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
	partial_quickersort (array, lower, j - 1);
	partial_quickersort (array, i, upper);
    }
}


/*
 |  void  sedgesort (array, len)
 |  KEY_T  array[];
 |  int    len;
 |
 |  Abstract:
 |	Sort array[0..len-1] into increasing order.
 |
 |  Method:
 |	Use partial_quickersort() with a sentinel (ala Sedgewick)
 |	to reach a partial order, leave the unsorted segments of
 |	length == CUTOFF to a simpler low-overhead, insertion sort.
 |
 |	This method is the fastest in this collection according
 |	to my experiments.
 |
 |  BIG NOTE:
 |	precondition: array[len] must hold a sentinel (largest
 |	possible value) in order for this to work correctly.
 |	An easy way to do this is to declare an array that has
 | 	len+1 elements [0..len], and assign MAXINT or some such
 |	to the last location before starting the sort (see sorttest.c)
 */
void  sedgesort (array, len)
register KEY_T  array[];
register int    len;
{
    /*
     * ------------------------- NOTE --------------------------
     * ignoring BIG NOTE above may lead to an infinite loop here
     * ---------------------------------------------------------
     */
    partial_quickersort (array, 0, len - 1);
    insort (array, len);
}


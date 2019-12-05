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
 |  void  heapsort (array, len)
 |  KEY_T  array[];
 |  int    len;
 |
 |  Abstract:	Sort array[0..len-1] into increasing order.
 |
 |  Method:	Heap-sort (ala Jon Bentley)
 |
 |  Advantages:
 |
 |	1. Worst case complexity is O (n log(n))
 |	2. Method of choice when only the smallest n elemens are wanted
 |	   and not a full ordering (use sift n times).
 */

void  heapsort (KEY_T array[], int len)
{
    register int	i;
    register KEY_T	temp, *sa = array - 1;
    /*
     |  'sa[]' is 'array[]' "shifted" one position to the left
     |  i.e.  sa[i] == array[i - 1]  (in particular:   sa[1] == array[0])
     |  'sa' has "Pascalish" indices and is thus more convenient
     |  for heap-sorting. An index i obeys the law:
     |	left_child (i) == 2i,  right_child (i) == 2i + 1
     |  Note: we don't use a[-1] which is outside our range, we just
     |  fake an array that starts one address lower, so we can refer
     |  to its first element as a[1] (rather than as a[0])
     */

    /* first step: make 'sa[]' a heap using siftdown len/2 times */
    for (i = len / 2; i >= 1; i--)
	siftdown (sa, i, len);

    /* heapify N more times, to reach complete order */
    for (i = len; i >= 2; i--) {
	SWAP(sa[1], sa[i]);
	siftdown (sa, 1, i - 1);
    }
}


/*
 |  void  siftdown (array, lower, upper)
 |  KEY_T  array[];
 |  int    lower, upper;
 |
 |  Abstract:
 |	Assume array[] is a heap except array[lower] is not in order.
 |	Sift array[lower] down the heap as long as it is bigger than
 |	its two children nodes. Preserving the heap condition.
 |
 |	Optimization: rather than swapping array[i] with the greater
 |	of its children within the loop, we save array[lower]
 |	before the loop, shift the inner values within the loop, and
 |	finally plug the saved value into its final location.
 */
void  siftdown (KEY_T array[], int lower, int upper)
{
    register int	i = lower, c = lower;
    register int	lastindex = upper/2;
    register KEY_T	temp;

    temp = array[i];
    while (c <= lastindex) {
	c = 2 * i;		/* c = 2i is the left-child of i */
	if (c + 1 <= upper  &&  GT(array[c + 1], array[c]))
	    c++;		/* c is the greatest child of i */
	if (GE(temp, array[c])) break;
	array[i] = array[c];
	i = c;
    }
    array[i] = temp;
}


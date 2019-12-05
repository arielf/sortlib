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
 |  void  shellsort (array, len)
 |  KEY_T  array[];
 |  int    len;
 |
 |  Abstract:	Sort array[0..len-1] into increasing order.
 |
 |  Method:	Shell sort (ala Kernighan & Ritchie)
 */

void shellsort (array, len)
register KEY_T  array[];
register int    len;
{
    register int	gap, i, j;
    register KEY_T	temp;

    for (gap = len / 2; gap > 0; gap /= 2)
	for (i = gap; i < len; i++)
	    for (j = i-gap; j >= 0 && GT(array[j], array[j + gap]); j -= gap) {
		SWAP(array[j], array[j + gap]);
	    }
}


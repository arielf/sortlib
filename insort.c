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
 |  void  insort (array, len)
 |  KEY_T  array[];
 |  int    len;
 |
 |  Abstract:	Sort array[0..len-1] into increasing order.
 |
 |  Method:	Optimized insertion-sort (ala Jon Bentley)
 */

void  insort (array, len)
register KEY_T  array[];
register int    len;
{
	register int	i, j;
	register KEY_T	temp;

	for (i = 1; i < len; i++) {
		/* invariant:  array[0..i-1] is sorted */
		j = i;
		/* customization bug: SWAP is not used here */
		temp = array[j];
		while (j > 0 && GT(array[j-1], temp)) {
			array[j] = array[j-1];
			j--;
		}
		array[j] = temp;
	}
}


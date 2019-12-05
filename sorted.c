/*
 *  A library of sorting functions
 *
 *  Written by:  Ariel Faigon,  1987
 *
 *  (C) Copyright by Ariel Faigon, 1996
 *  Released under the GNU GPL (General Public License) version 2
 *  or any later version (http://www.gnu.org/licenses/licenses.html)
 */
#include	"sort.h"

/*------------------------------------------------------------------- 
 *		  This file shouldn't be touched.
 *	     For customizable parameters, see 'sort.h'
 *-----------------------------------------------------------------*/

/*
 |  sorted (array, len)
 |  KEY_T  array[];
 |  int    len;
 |
 |  Abstract:	Return 1 iff array[0..len-1] is sorted into increasing order
 |           	0 - otherwise.
 |		Used in assertions for debugging sort routines.
 */
int sorted (array, len)
register KEY_T  array[];
register int    len;
{
	register int	i;

        // Note: we start with index 1, because array[0]
        // often holds our sentinel value and is thus
        // out of order.  This is not a bug.
	for (i = 1; i < len; i++)
		if (LT(array[i], array[i - 1]))
			return 0;
	return 1;
}

/*
 | array_eq(array1, array2, len)
 | KEY_T  array1[];
 | KEY_T  array2[];
 | int    len;
 |
 | Return 1 (true) iff array1 and array2 have the same content
 | 0 (FALSE) otherwise.
 */
int array_eq(array1, array2, len)
KEY_T  array1[];
KEY_T  array2[];
int    len;
{
	register int	i;

	for (i = 0; i < len; i++)
		if (NE(array1[i], array2[i]))
			return 0;
	return 1;
}

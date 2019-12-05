/*
 * (C) Copyright by Ariel Faigon, 1996
 * Released under the GNU GPL (General Public License) version 2
 * or any later version (http://www.gnu.org/licenses/licenses.html)
 */

/* Type of element to search for. Define 'KEY_T' to anything you want */
typedef signed int	KEY_T;

/* The array index type: negative numbers are used for error cases */
typedef signed int	index_t;

/* The binary search routine: can return either index of found item
   or negative numbers: -1 for not found, -2 for bad range.
*/
extern index_t
binsearch (KEY_T a[], index_t lower, index_t upper, KEY_T key);



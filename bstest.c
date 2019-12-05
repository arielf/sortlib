/*
 * (C) Copyright by Ariel Faigon, 1996
 * Released under the GNU GPL (General Public License) version 2
 * or any later version (http://www.gnu.org/licenses/licenses.html)
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"bsearch.h"

KEY_T	*a;	/* Pointer to the array to be sorted */

int main (argc, argv)
int   argc;
char  *argv[];
{
	KEY_T		j;
	int		pos, len = 100;

	switch (argc) {
	    case 2:
		len = atoi(argv[1]);
		if (len > 0) break;
	    default:
		fprintf(stderr,"Usage:  %s array_length\n", argv[0]);
		exit (1);
	}

	if ((a = (KEY_T *) malloc((unsigned) (len+1)*sizeof(KEY_T))) == NULL) {
		perror("malloc");
		exit (1);
	}

	/* Fill array */
	for (j = 0; j < len; j++)
		a[j] = j;


	for (j = 0; j < len; j++) {
		pos = binsearch (a, 0, len-1, j);
#ifdef DEBUG
		printf("a[%d] = %d\n", pos, j);
#endif
		assert(pos == j);

		/* if it is greater than j/2
		 * it cannot be in the lower half of the array
		 */
		if (j > len/2)
			assert(binsearch (a, 0, len/2, j) == -1);
	}
	/* values that cannot be found in a[] */
	assert(binsearch (a, 0, len - 1, -1) == -1);
	assert(binsearch (a, 0, len - 1, -2) == -1);
	assert(binsearch (a, 0, len - 1, len) == -1);

	/* Illegal range: upper < lower cases */
	assert(binsearch (a, len, len - 1, -1) == -2);
	assert(binsearch (a, len, len - 1, 0) == -2);

	return 0;
}


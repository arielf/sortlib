/*
 *  (C) Copyright by Ariel Faigon, 1996
 *  Released under the GNU GPL (General Public License) version 2
 *  or any later version (http://www.gnu.org/licenses/licenses.html)
 */
#include	<limits.h>
#include	<assert.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<errno.h>
#include	<sys/time.h>
#include	<unistd.h>

#include	"sort.h"

#ifdef DEBUG
static void	printarray ();
#endif

typedef  void (* FUNC_T) ();

typedef struct {
	FUNC_T		f;	// Pointer to function
	char *		name;	// name of function
} FUNC_STRUCT;

//
// Array of sorting functions to test
//
FUNC_STRUCT sfunc[] = {
	{ insort,		"insort" },
	{ shellsort,		"shellsort" },
	{ heapsort,		"heapsort" },
	{ gamasort,		"gamasort" },
	{ quicksort,		"quicksort" },
	{ quickersort,		"quickersort" },
	{ sedgesort,		"sedgesort" },
	{ NULL,			"" }
};

KEY_T	*ain;	// Pointer to input (unsorted) array
KEY_T	*aout;	// Pointer to reference (sorted) array
KEY_T	*a;	// Pointer to the array to be sorted

int main (argc, argv)
int   argc;
char  *argv[];
{
    int		i, len;
    KEY_T	max = 10;   // default
    FUNC_T	func;
    double	start_time, end_time;
    struct timeval tv;

    switch (argc) {
      case 3:
	max = atoi(argv[2]);
      case 2:
	len = atoi(argv[1]);
	if (len > 0) break;

      default:
	fprintf(stderr,"Usage:  %s array_length [range]\n", argv[0]);
	exit (1);
    }

    if ((ain = (KEY_T *)malloc((len+1)*sizeof(KEY_T))) == NULL) {
	fprintf(stderr, "ain=malloc() failed: %s\n", strerror(errno));
	exit (1);
    }
    if ((aout = (KEY_T *)malloc((len+1)*sizeof(KEY_T))) == NULL) {
	fprintf(stderr, "aout=malloc() failed: %s\n", strerror(errno));
	exit (1);
    }
    if ((a = (KEY_T *)malloc((len+1)*sizeof(KEY_T))) == NULL) {
	fprintf(stderr, "a=malloc() failed: %s\n", strerror(errno));
	exit (1);
    }

    a[len] = INT_MAX;		// Sentinel value to mark end of array
    aout[len] = INT_MAX;	// Sentinel value to mark end of array

    for (i = 0; i < len; i++)	// Fill array with random values
	ain[i] = random() % (max + 1);

    memcpy(aout, ain, sizeof(KEY_T)*len);	// copy input to output array

    // sort the output array with with a reference sort routine
    shellsort(aout, len);

#ifdef DEBUG
    puts("=== Unsorted array:");
    printarray(ain, len); puts("\n");
#endif

    setbuf(stdout, NULL);

    printf("Benchmarking & verifying sort funcs on %u element array\n", len);

    for (i = 0; (func = sfunc[i].f) != NULL; i++) {

	memcpy(a, ain, sizeof(KEY_T)*len);    // initialize array to be sorted

	printf("%s: %*s", sfunc[i].name, 12 - (int)strlen(sfunc[i].name), " ");

        // start performance stopwatch
	gettimeofday(&tv, NULL);
	start_time = (double) tv.tv_sec * 1000000 + tv.tv_usec;

	//
	// Sort the array
	//
	if (func == quicksort ||
	       func == quickersort || func == partial_quickersort) {
	    (*func)(a, 0, len - 1);
	} else if (func == gamasort) {
	    (*func)(a, 0, len);
	} else {
            /* classic, simple interface to sort, just array+len */
	    (*func)(a, len);
	}

        // stop performance stopwatch
	gettimeofday(&tv, NULL);
	end_time = (double) tv.tv_sec * 1000000 + tv.tv_usec;
	printf("%10lu microsec.\n", (unsigned long) (end_time - start_time));

        //
        // check correctness
        //
	if (func != partial_quickersort) {
	    // 1) Check that array is sorted
	    assert(sorted(a, len));

	    // 2) and is the same as reference sorted array
	    assert(array_eq(a, aout, len));
	}
#ifdef DEBUG
	printarray(a, len); puts("\n");
#endif
    }
    return 0;
}


#ifdef DEBUG

/*
 |  static void  printarray (array, len)
 |  KEY_T  array[];
 |  int  len;
 |
 |  Abstract:	Print out array[0..len-1].
 */
static void printarray (array, len)
register KEY_T  array[];
register int    len;
{
    register int	i;

    for (i = 0; i < len; i++)
	printf("%d ", array[i]);
}

#endif


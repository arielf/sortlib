/*
 * Gamasort:
 *	Contributed by Jose' Gama,
 *	Slightly optimized for speed by Ariel Faigon
 *	2009-12-29: SEGV crash fixed by Ariel Faigon
 *	(Bug report by Joe Sylvester, thanks!)
 *
 * This is a Radix Sort Exchange routine which will work only on
 * unsigned integers (unlike a general sorting function which
 * works based on comparisons).  Since its complexity overhead
 * is pretty large, it is efficient on big array where the
 * maximum number is bounded by a relatively small ceiling.
 * E.g. a big array of bytes or shorts.
 *
 * The algorithm is pretty simple:
 * 1) It will first find the maximum number in order to see
 *    if it can skip some radices.  Then it proceeds to order
 *    from the numbers with the most-significant set-bit downwards
 * 2) It leaves the unsorted segments of length == CUTOFF unsorted.
 * 3) From higher bit to lower it will compare numbers
 *    based on the bit being scanned.  This process is
 *    improved by using 2 pivots that will move 0's to the
 *    left and 1's to the right.
 * 4) When finding the pivots it looks for the best case
 *    of all 0's or 1's to skip more scanning.
 * 5) A low overhead Insertion Sort finishes the job.
 *
 */

#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

/* 15 has been found empirically as the optimal cutoff value in 1996 */
/* In 2006, with computers very different and much faster it was found
 * to be a close tie between 15 and 16 */
#ifndef CUTOFF
#  define CUTOFF 15
#endif

static int lg (int x)
{
    return (int) (log10(x) / log10(2));
}

//
// Slow version of insertion sort
// see insort.c for a significantly faster version
//
static void insertionsort(KEY_T a[], int i, int j)
{
     int temp, d, c;

     for (c = j-1; c >= i; c--) {
          temp = a[c];
          for (d = c+1; d <= j && (temp > a[d]); d++)
               a[d-1] = a[d];
          a[d-1] = temp;
     }
}

//
// Recursive version of GamaSort
//
static void GamaSort(KEY_T array[], int lo, int up, int bit)
{
    register KEY_T	temp;
    register long	b, u, l;

    if (up - lo > CUTOFF) {

	b = (1 << bit);		// b = 2^bit
	u = up; l = lo;		// 2 pivots

	while (((b & array[u]) == b) && (u > lo))
	    u--;		//check 1's from the right

	if (!((u == lo) && ((b & array[u]) == b))) {
	    while (((b & array[l]) == 0) && (l < up))
		l++;		//check 0's from the left
	}

	if ((u == lo && (b & array[u]) == b) ||
	    (l == up && (b & array[l]) == 0)) {
	    u = up + 1;		// it's all 0's or 1's, skip it
	} else {
	    while (l < u) {
		if (((b & array[l]) == b) && ((b & array[u]) == 0)) {
		    SWAP(array[u], array[l]);
		    while (((b & array[u]) == b) && (u > lo))
			u--;
		}
		l++;
	    }
	}
	if (l >= u)
	    u++;

	if (bit > 0) {
	    if (u - 1 > lo)
		GamaSort(array, lo, u-1, bit-1);	// left
	    if (up > u)
		GamaSort(array, u, up, bit-1);		// right
	}
    }
}

//
// Main version of gamasort (call this one)
//
void gamasort(KEY_T array[], int lo, int up)
{
    KEY_T   ubits, i, temp, max = INT_MIN, maxidx;

    for (i = 0; i <= up; i++) {
	if (array[i] >= max) {
	    max = array[i];
	    maxidx = i;
	}
    }
    SWAP(array[up], array[maxidx]);
    ubits = lg(array[maxidx]);
    GamaSort(array, lo, up, ubits);
    // insertionsort(array, lo, up);	// this version is slow...
    insort(array, up);
}


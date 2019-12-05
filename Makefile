#
# Makefile for sorting library
#

# compiler selection: prefer clang to gcc
CC = $(shell which clang)
ifeq ($(CC),)
    CC = gcc
endif

ifeq ($(CC),)
    $(warning No compiler found)
    exit 1
endif

# Number of array elements for testing
N_ELEMENTS=100000
# When to switch from n*log(n) to n^2 method (gamasort & sedgesort)
CUTOFF=50

ifeq ($(DEBUG),)
	# fast run-time
	CFLAGS = -O3 -fomit-frame-pointer -DCUTOFF=$(CUTOFF)
else
	# debugging
	CFLAGS = -ag -DCUTOFF=$(CUTOFF)
endif

SORTOBJ = sorted.o insort.o shellsort.o gamasort.o \
	quicksort.o quickersort.o sedgesort.o heapsort.o

all: sorttest bstest

sorttest: sorttest.o sort.a
	$(CC) $(CFLAGS) sorttest.o sort.a -o $@ -lm

bstest: bstest.o bsearch.o
	$(CC) $(CFLAGS) bstest.o bsearch.o -o $@

sort.a: $(SORTOBJ)
	ar rv $@ $(SORTOBJ)

clean clobber c: .FORCE
	-rm sorttest bstest *.o *.a

.c.o:
	$(CC) $(CFLAGS) -c $*.c

tar tgz: sort-all.tgz

sort-all.tgz: .FORCE
	cd ..; tar cvf - sort/*.[ch] sort/Makefile sort/gpl.txt | \
		gzip -9 > $@ && mv $@ sort/

.FORCE: ;

test check: all
	@echo === checking sort routines
	@sorttest $(N_ELEMENTS) 99999999 && echo === OK
	@echo === checking binary-search routines
	@bstest 7007 && echo === OK

$(SORTOBJ): sort.h


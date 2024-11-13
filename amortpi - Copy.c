
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MCERR 24

// prototypes for callback functions
void (*callEset)(int) = NULL;

// amortpi.c - lrb - 11/19/18, 6/8/19

int amort(int nargs, int *args) {
	int* amount = (int*)args[0];
	int* principle = (int*)args[1];
	int* interest = (int*)args[2];
	int* result = (int*)args[3];

	double a = (double)amount[0] / (double)amount[1];
	double p = (double)principle[0] / (double)principle[1];
	double I = (double)interest[0] / (double)interest[1];
	double lg = log(a / (a - I * p)) / log(1 + I);
	result[0] = floor(lg * 100); // 6/8/19
	result[1] = 100; // 6/8/19
	}

/*	INFRASTRUCTURE...
 *	Comment out your test main and uncomment this infrastructure.
 *	first in this list is MC 1001. Change the names to functions
 *	written above. Enlarge the list for larger libraries.
 */
typedef int (*McList)(int,int*);

McList plugInList[] =
	{ &amort
	};

/*	code the MC above and register in McList array. Placement in the array
 *	determines the MC number starting with 1001.
 */
void plugInMC(int mcno, int nargs, int *args) {
	if (mcno<1 || mcno>(sizeof(plugInList) / sizeof(void*))) {
		callEset(MCERR);
	}
	else {
	    int x = plugInList[mcno-1](nargs, args);
	}
}

// register callbacks to specific tc functions...
void register_eset( int eset )
{
	callEset = eset;
}


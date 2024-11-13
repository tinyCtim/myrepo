
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MCERR 24

// prototypes for callback functions
void (*callEset)(int) = NULL;

// spiralpi.c - lrb - 1/2/19

int spiralx(int nargs, int *args) {
	int t = args[0];
	int scale1 = args[1];
	int scale2 = args[2];
	int* result = (int*)args[3];
	int a = args[4];
	double td;
	td = (double)t / (double)scale1;
	double f;
	f = exp(a / 100. * td) * cos(td);
	f = f * scale2;
	f = floor(f);
	result[0] = f;
	}

int spiraly(int nargs, int *args) {
	int t = args[0];
	int scale1 = args[1];
	int scale2 = args[2];
	int* result = (int*)args[3];
	int a = args[4];
	double td;
	td = (double)t / (double)scale1;
	double f;
	f = exp(a / 100. * td) * sin(td);
	f = f * scale2;
	f = floor(f);
	result[0] = f;
	}

/*	INFRASTRUCTURE...
 *	Comment out your test main and uncomment this infrastructure.
 *	first in this list is MC 1001. Change the names to functions
 *	written above. Enlarge the list for larger libraries.
 */
typedef int (*McList)(int,int*);

McList plugInList[] =
	{ &spiralx,&spiraly
	};

/*	code the MC above and register in McList array. Placement in the array
 *	determines the MC number starting with 1001.
 */
void plugInMC(int mcno, int nargs, int *args) {
	if(mcno<1 || mcno>(sizeof(plugInList)/sizeof(void*))) {
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

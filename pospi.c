#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define MCERR 24

// prototypes for callback functions
void (*callEset)(int) = NULL;

// pospi.c - lrb - 6/29/19

int pos(int nargs, int *args) {
 int* c = (int*)args[0];
 int* r = (int*)args[1];
 char* msg = (int*)args[2];
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD posxy = {c, r};
 SetConsoleCursorPosition(hConsole, posxy);
 WriteConsole(hConsole, msg, strlen(msg), NULL, NULL);
 }

/*	INFRASTRUCTURE...
 *	Comment out your test main and uncomment this infrastructure.
 *	first in this list is MC 1001. Change the names to functions
 *	written above. Enlarge the list for larger libraries.
 */
typedef int (*McList)(int,int*);

McList plugInList[] =
	{ &pos
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

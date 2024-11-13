#include <stdio.h>
#include <stdlib.h>
#include "library.h"

/*
 *
 * chapter.2.1.c
 * 2/28/20 3/1,2/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html
 *
 * to compile
 *
 * gcc chapter.2.1.c library.o -o chapter.2.1.exe (Windows)
 * gcc chapter.2.1.c library.o -o chapter.2.1 (Linux)
 *
 * to run
 *
 * chapter.2.1.exe (Windows)
 * ./chapter.2.1 (Linux)
 *
 * read n, then n minutes and seconds pairs, display fastest and slowest
 * pace and average pace
 *
 */

int main(void) {
	printf("\nchapter.2.1.c - 3/2/20 - lrb\n");
	int n,i;
	int minutes,seconds;
	int total_seconds=0;
	int min=999,max=0;
	int total;
	printf("\nenter n : ");
	scanf("%d",&n);
	for (i=1;i<=n;++i) {
		printf("\nenter minutes : ");
		scanf("%d",&minutes);
		printf("\nenter seconds : ");
		scanf("%d",&seconds);
		total=minutes*60+seconds;
		if (total<min) min=total;
		if (total>max) max=total;
		total_seconds+=total;
	}
	total_seconds/=n;
	show_pace("fastest pace", min);
	show_pace("slowest pace", max);
	show_pace("average pace", total_seconds);
	exit(0);
}

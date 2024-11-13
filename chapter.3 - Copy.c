#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*
 *
 * chapter.3.c
 * 3/3/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#3
 *
 * to compile
 *
 * gcc chapter.3.c library.o -o chapter.3.exe (Windows)
 * gcc chapter.3.c library.o -o chapter.3 (Linux)
 *
 * to run
 *
 * chapter.3.exe (Windows)
 * ./chapter.3(Linux)
 *
 * read n, then n mile,mm:ss pairs. display fastest mile and pace, slowest
 * mile and pace and average pace.
 *
 */

int main(void) {
	printf("\nchapter.3.c - 3/3/20 - lrb\n");
	char mile_pace[20],mm[20],ss[20],mile[20],max_mile[20],min_mile[20];
	char *index;
	int n,i,minutes,seconds;
	int total_seconds = 0,min = 999,max = 0,total;
	printf("\nenter n : ");
	scanf("%d", &n);
	for (i = 1;i <= n;++i) {
		printf("\nenter mile,mm:ss (e.g. 3.1,13:25): ");
		scanf("%s", &mile_pace);
		index = strchr(mile_pace, ',');
		*index = 0;
		strcpy(mile, mile_pace); // 3.1,13:25 -> 3.1 -> mile
		strcpy(mile_pace, ++index); // 3.1,13:25 -> 13:25
		index = strchr(mile_pace, ':');
		*index = 0;
		strcpy(mm, mile_pace); // 13:25 -> 13 -> mm
		strcpy(ss, ++index); // 25 -> ss
		minutes = atoi(mm);seconds = atoi(ss);
		total = minutes*60+seconds;
		if (total < min) {
			min = total;
			strcpy(min_mile, mile);
		}
		if (total > max) {
			max = total;
			strcpy(max_mile, mile);
		}
		total_seconds += total; // update total seconds
	}
	total_seconds /= n; // get average
	printf("\nmile %s\n", min_mile);
	show_pace("fastest pace", min);
	printf("\nmile %s\n", max_mile);
	show_pace("slowest pace", max);
	show_pace("average pace", total_seconds);
	exit(0);
}

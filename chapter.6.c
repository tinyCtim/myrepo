#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*
 *
 * chapter.6.c
 * 3/6/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#6
 *
 * to compile
 *
 * gcc chapter.6.c library.o -o chapter.6.exe (Windows)
 * gcc chapter.6.c library.o -o chapter.6 (Linux)
 *
 * to run
 *
 * chapter.6.exe (Windows)
 * ./chapter.6 (Linux)
 *
 * read a line feed delimited text file, tnen a starting record number and
 * an ending reoord number, then print these records and the average pace
 *
 */

int main(void)
{
	char mm[20],ss[20];
	char *index;
	int n,m,i,minutes,seconds;
	int total,total_seconds = 0;
	char records[100][30];
	i = 0;
	printf("\nchapter.6.c - 3/6/20 - lrb\n");
	char buffer[5000];
	char filename[30];
	FILE *fp;
	printf("\nenter name of file to read : ");
	scanf("%s", &filename);
	if ((fp = fopen(filename,"r")) == NULL) {
		printf("\nerror on file open");exit(1);
	}
	fread(buffer, 1 , 5000, fp);
	fclose(fp);
	while ((index = strchr(buffer,'\n')) != 0) {
		*index = 0;
		strcpy(records[i++], buffer);
		strcpy(buffer, ++index);
	}
	printf("\nEnter starting record number ");
	scanf("%d", &n);
	printf("\nEnter ending record number ");
	scanf("%d", &m);
	for (i = n; i <= m; ++i) {
		printf("\n%s", records[i]);
		index = strchr(records[i], ',');
		*index = 0;
		strcpy(records[i], ++index); // 3.1,13:25 -> 13:25
		index = strchr(records[i], ':');
		*index = 0;
		strcpy(mm, records[i]); // 13:25 -> 13 -> mm
		strcpy(ss, ++index); // 25 -> ss
		minutes = atoi(mm);seconds = atoi(ss);
		total = minutes*60+seconds;
		total_seconds += total; // update total seconds
	
	}
	total_seconds /= (m-n+1); // get average
	printf("\n");
	show_pace("average pace", total_seconds);
	exit(0);
}

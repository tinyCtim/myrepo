#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*
 *
 * chapter.8.c
 * 3/9/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#8
 *
 * to compile
 *
 * gcc chapter.8.c library.o -o chapter.8.exe (Windows)
 * gcc chapter.8.c library.o -o chapter.8 (Linux)
 *
 * to run
 *
 * chapter.8.exe [-f filename] [-n num] (Windows)
 * ./chapter.8 [-f filename] [-n num] (Linux)
 *
 * print the average pace for each num contiguous records
 * print the fastest average pace of any num contiguous records
 * print the slowest average pace of any num contiguous records
 *
 */

int main(int argc, char *argv[])
{
	char *index;
	int i;
	float foo, f1, total, total_seconds, min = 99999, max = 0;
	char records[1000][30] = {{""}};
	printf("\nchapter.8.c - 3/9/20 - lrb\n");
	char filename[30] = "mph.txt";
	int num = 1;
	printf("\nUsage : chapter.8 [-f filename] [-n num]\n");
	for (i = 1;i < argc;i++) {
		if (strcmp(argv[i],"-n") == 0) num = atoi(argv[++i]);
		if (strcmp(argv[i],"-f") == 0) strcat(filename, argv[++i]);
	}
	char buffer[5000];
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("\nerror on file open");exit(1);
	}
	fread(buffer, 1, 5000, fp);
	fclose(fp);
	int record_count = 0;
	i = 0;
	char records_work[30];
	while ((index = strchr(buffer, '\n')) != 0) {
		++record_count;
		*index = 0;
		strcpy(records[i++], buffer);
		strcpy(buffer, ++index);
	}
	printf("\nrecord count %d\n", record_count);
	if (num >= record_count) {
		printf("\n-n option of %d must not be >= %d" \
		,num,record_count);exit(1);
	}
	int start_record = 0;
	while (start_record+num < record_count) {
		total_seconds = 0;
		for (i = start_record;i < start_record+num;++i) {
			strcpy(records_work, records[i]);
			f1 = strtof(records_work, NULL);
			foo = 1/f1*3600; // convert mph to spm
			printf("\nseconds per mile %.2f", foo);
			total = foo;
			total_seconds += total;
		}
		total_seconds /= num;
		if (total_seconds > max) max = total_seconds;
		if (total_seconds < min) min = total_seconds;
		printf("\n\naverage pace over this %d record stretch", num);
		show_pace("", (int)total_seconds);
		++start_record;
	}
	show_pace("\nfastest average pace", (int)min);
	show_pace("\nslowest average pace", (int)max);
	exit(0);
}

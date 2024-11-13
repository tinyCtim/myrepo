#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*
 *
 * chapter.7.c
 * 3/7/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#7
 *
 * to compile
 *
 * gcc chapter.7.c library.o -o chapter.7.exe (Windows)
 * gcc chapter.7.c library.o -o chapter.7 (Linux)
 *
 * to run
 *
 * chapter.7.exe -f filename [-n num] (Windows)
 * ./chapter.7 -f filename [-n num] (Linux)
 *
 * print the average pace for each num contiguous records
 * print the fastest average pace of any num contiguous records
 * print the slowest average pace of any num contiguous records
 *
 */

int main(int argc, char *argv[])
{
	char mm[20],ss[20];
	char *index;
	int i,minutes,seconds;
	int total;
	int total_seconds;
	char records[100][30] = {""};
	printf("\nchapter.7.c - 3/7/20 - lrb\n");
	char filename[30] = "";
	int num = 1;
	if (argc == 1) {
		printf("\nUsage : chapter.7 -f filename [-n num]\n");exit(1);
	}
	for (i = 1;i < argc;i++) {
		if (strcmp(argv[i],"-n") == 0) num = atoi(argv[++i]);
		if (strcmp(argv[i],"-f") == 0) strcat(filename, argv[++i]);
	}
	if (strlen(filename) == 0) {
		printf("\nfilename must be provided\n");exit(1);
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
	int min = 99999,max = 0;
	while (start_record+num < record_count) {
		total_seconds = 0;
		for (i = start_record;i < start_record+num;++i) {
			strcpy(records_work, records[i]);
			printf("\n%s", records_work);
			index = strchr(records_work, ',');
			*index = 0;
			strcpy(records_work, ++index); // 3.1,13:25 -> 13:25
			index = strchr(records_work, ':');
			*index = 0;
			strcpy(mm, records_work); // 13:25 -> 13 -> mm
			strcpy(ss, ++index); // 25 -> ss
			minutes = atoi(mm);seconds = atoi(ss);
			total = minutes*60+seconds;
			total_seconds += total;
		}
		total_seconds /= num;
		if (total_seconds > max) max = total_seconds;
		if (total_seconds < min) min = total_seconds;
		printf("\n\naverage pace over this %d record stretch", num);
		show_pace("", total_seconds);
		putchar(10);
		++start_record;
	}
	show_pace("\nfastest average pace", min);
	show_pace("\nslowest average pace", max);
	exit(0);
}

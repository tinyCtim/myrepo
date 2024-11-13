
/*
 *
 * http://garmin.stevegordon.co.uk/
 *
 * .csv file format produced:
 *
 * f1,f2,d3,f4,f5,d6,d7,d8,f9
 * 
 * Where:
 * 
 *     f1 = latitude in degrees (fractional value)
 *     f2 = longitude in degrees (fractional value)
 *     d3 = cumulative time in seconds (decimal value)
 *     f4 = cumulative distance in miles (fractional value)
 *     f5 = instantaneous speed in mph (fractional value)
 *     d6 = heart rate in bpm (decimal value)
 *     d7 = cadence in rpm (decimal value)
 *     d8 = power in watts (decimal value)
 *     f9 = elevation in metres (fractional value)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/*
 *
 * chapter.8.1.c
 * 3/11/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#8.1
 *
 * to compile
 *
 * gcc chapter.8.1.c library.o -o chapter.8.1.exe (Windows)
 * gcc chapter.8.1.c library.o -o chapter.8.1 (Linux)
 *
 * to run
 *
 * chapter.8.1.exe [-f filename] [-n num] (Windows)
 * ./chapter.8.1 [-f filename] [-n num] (Linux)
 *
 * print the average pace for each num contiguous records
 * print the fastest average pace of any num contiguous records
 * print the slowest average pace of any num contiguous records
 *
 */

int main(int argc, char *argv[])
{
	char *index;
	int i, j;
	float f5, total, total_seconds, min = 99999, max = 0;
	char records[1000][60] = {{""}};
	printf("\nchapter.8.1.c - 3/11/20 - lrb\n");
	char filename[30] = "11128_A3BA4213.FIT";
	int num = 25;
	printf("\nUsage : chapter.8.1 [-f filename] [-n num]");
	printf("\n\nfilename is a .FIT file which has been converted");
	printf("\nto a comma separated value file by");
	printf("\nhttp://garmin.stevegordon.co.uk/");
	printf("\n\nnum defaults to 25 which corresponds to a .25 mile stretch.");
	printf("\nA num of 100 would be a 1.0 mile stretch.\n");
	for (i = 1;i < argc;i++) {
		if (strcmp(argv[i],"-n") == 0) num = atoi(argv[++i]);
		if (strcmp(argv[i],"-f") == 0) strcat(filename, argv[++i]);
	}
	char buffer[30000];
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("\nerror on file open");exit(1);
	}
	fread(buffer, 1, 30000, fp);
	fclose(fp);
	int record_count = 0;
	i = 0;
	char records_work[60];
	while ((index = strchr(buffer, '\n')) != 0) {
		++record_count;
		*index = 0;
		strcpy(records[i++], buffer);
		strcpy(buffer, ++index);
	}
	printf("\nrecord count %d\n", record_count);
	if (num >= record_count || num <= 1) {
		printf("\n-n option must be > 1 and < %d" \
		,record_count);exit(1);
	}
	int start_record = 0;
	// 41.6870772,-72.7191867,3799,3.41,3.4,255,58,,,,
	while (start_record+num < record_count) {
		total_seconds = 0;
		for (i = start_record;i < start_record+num;++i) {
			strcpy(records_work, records[i]);
			for (j = 1;j <= 4;++j) {
				index = strchr(records_work, ',');
				strcpy(records_work, ++index);
			}
			index -= 2;
			*index = 0;
			f5 = strtof(records_work, NULL);
			if (f5 < .1) continue; // skip 1st record
			total_seconds += f5;
		}
		total_seconds = total_seconds/num;
		total_seconds = 1/total_seconds*3600;
		if (total_seconds > max) max = total_seconds;
		if (total_seconds < min) min = total_seconds;
		printf("\naverage pace over this %0.2f mile stretch", num/100.);
		show_pace("", (int)total_seconds);
		start_record += num;
	}
	show_pace("\n\nfastest average pace", (int)min);
	show_pace("\nslowest average pace", (int)max);
              printf("\n");
	exit(0);
}

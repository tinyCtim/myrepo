
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
 * chapter.8.2.c
 * 3/13/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#8.2
 *
 * to compile
 *
 * gcc chapter.8.2.c -o chapter.8.2.exe (Windows)
 * gcc chapter.8.2.c -o chapter.8.2 (Linux)
 *
 * to run
 *
 * chapter.8.2.exe [-f filename] [-n num] (Windows)
 * ./chapter.8.2 [-f filename] [-n num] (Linux)
 *
 * print the average pace for each num consecutive records
 * print the fastest average pace of any num consecutive records
 * print the slowest average pace of any num consecutive records
 *
 */

int main(int argc, char *argv[])
{
	char *index;
	int i;
	float pace, d3, f4, start_seconds, stop_seconds, start_distance, \
stop_distance, min = 99, max = 0;
	char records[1000][60] = {{""}};
	printf("\nchapter.8.2.c - 3/13/20 - lrb\n");
	char filename[30] = {""};
	int num = 30;
	printf("\nUsage : chapter.8.2 -f filename [-n num]");
	printf("\n\nfilename is a .FIT file which has been converted");
	printf(" to a comma separated value file by");
	printf(" http://garmin.stevegordon.co.uk/");
	printf("\n\nnum defaults to 30 which corresponds to approximately .25 mile stretches.");
	printf("\nuse a larger num for longer stretches, a smaller num for shorter stretches.");
	for (i = 1;i < argc;i++) {
		if (strcmp(argv[i],"-n") == 0) num = atoi(argv[++i]);
		if (strcmp(argv[i],"-f") == 0) strcat(filename, argv[++i]);
	}
	if (strlen(filename) == 0) {printf("\nfilename required\n");exit(1);}
	char buffer[30000];
	FILE *fp;
	fp = fopen(filename, "r");
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
	printf("\n\nrecord count %d\n", record_count);
	if (num >= record_count-10 || num <= 3) {
		printf("\n-n option must be < %d and > 3" \
, record_count-10);exit(1);
	}
	int start_record = 9; // skip first few records
	// 41.6870772,-72.7191867,3799,3.41,3.4,255,58,,,,
	//                        d3   f4
	while (start_record < record_count-num) {
//		printf("\nstart_record %d", start_record);
		strcpy(records_work, records[start_record]);
		index = strchr(records_work, ',');
		strcpy(records_work, index+1);
		index = strchr(records_work, ',');
		strcpy(records_work, index+1);
		index = strchr(records_work, ',');
		*index = 0;
//		printf("\n%s", records_work);
		d3 = strtof(records_work, '\0');
		start_seconds = d3;
		strcpy(records_work, index+1);
		index = strchr(records_work, ',');
		*index = 0;
//		printf("\n%s", records_work);
		f4 = strtof(records_work, '\0');
		start_distance = f4;
		start_record += num-1;
		strcpy(records_work, records[start_record]);
		index = strchr(records_work, ',');
		strcpy(records_work, index+1);
		index = strchr(records_work, ',');
		strcpy(records_work, index+1);
		index = strchr(records_work, ',');
		*index = 0;
//		printf("\n%s", records_work);
		d3 = strtof(records_work, '\0');
		stop_seconds = d3;
		strcpy(records_work, index+1);
		index = strchr(records_work, ',');
		*index = 0;
//		printf("\n%s", records_work);
		f4 = strtof(records_work, '\0');
		stop_distance = f4;

//		printf("\nstart_seconds %4.0f start_distance %2.3f \
stop_seconds %4.0f stop distance %2.3f", start_seconds, start_distance, \
stop_seconds, stop_distance);

		pace = (stop_seconds-start_seconds)/(stop_distance-start_distance)/60;

		if (pace > max) max = pace;
		if (pace < min) min = pace;
		printf("\navg. pace over this %2.3f mile stretch was \
%2.3f min. per mile", stop_distance-start_distance, pace);

		start_record += 1;
	}
	printf("\n\nfastest avg. pace %2.3f min. per mile", min);
	printf("\n\nslowest avg. pace %2.3f min. per mile", max);
	printf("\n");
	exit(0);
}

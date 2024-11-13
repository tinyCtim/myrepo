
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

/*
 *
 * chapter.8.2.1.c
 *
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#8.2.1
 *
 * to compile
 *
 * gcc chapter.8.2.1.c -o chapter.8.2.1.exe (Windows)
 * gcc chapter.8.2.1.c -o chapter.8.2.1 (Linux)
 *
 * to run
 *
 * chapter.8.2.1.exe -f filename [-n num] (Windows)
 * ./chapter.8.2.1 -f filename [-n num] (Linux)
 *
 * print the average pace for each num consecutive records
 * print the fastest average pace of any num consecutive records
 * print the slowest average pace of any num consecutive records
 *
 */

float pace, start_seconds, stop_seconds;
float start_distance, stop_distance, min, max;
char records[2000][60], *idx, records_work[60]; // 3/18/20

float parse(int comma)
{
	for (int i = comma;i > 0;--i) {
		idx = strchr(records_work, ',');
		if (i > 1) strcpy(records_work, idx+1);
	}
	*idx = 0;
	return strtof(records_work, '\0');
}

int main(int argc, char *argv[])
{
	int i, num = 30, record_count = 0;
	char filename[30] = {""}, buffer[100000]; // 3/18/20
	printf("\nchapter.8.2.1.c - 3/18/20 - lrb\n");
	printf("\nUsage : chapter.8.2.1 -f filename [-n num]");
	printf("\n\nfilename is a .FIT file which has been converted");
	printf("\nto a comma separated value file by");
	printf(" http://garmin.stevegordon.co.uk/");
	printf("\n\nnum defaults to 30 which corresponds to approximately .25 mile stretches.");
	printf("\nuse a larger num for longer stretches, a smaller num for shorter stretches.");
	for (i = 1;i < argc;i++) {
		if (strcmp(argv[i],"-n") == 0) num = atoi(argv[++i]);
		if (strcmp(argv[i],"-f") == 0) strcat(filename, argv[++i]);
	}
	if (strlen(filename) == 0) {printf("\n\nfilename required\n");exit(1);}
	FILE *fp;
	fp = fopen(filename, "r");
	int cnt = fread(buffer, 1, 100000, fp); // 3/18/20
	printf("\n\n%d bytes read\n",cnt); // 3/16/20
	fclose(fp);
	i = 0;
	while ((idx = strchr(buffer, '\n')) != 0) {
		++record_count;
		*idx = 0;
		strcpy(records[i++], buffer);
		strcpy(buffer, ++idx);
	}
	printf("\nrecord count %d\n", record_count);
	if (num >= record_count-10) num = record_count-11;
	if (num <= 5) num = 6;
	int start_record = 9; // skip first few records
	// 41.6870772,-72.7191867,3799,3.41,3.4,255,58,,,,
	//                        d3   f4
	min = 99, max = 0;
	while (start_record < record_count-num) {
		strcpy(records_work, records[start_record]);
		start_seconds = parse(3);
		strcpy(records_work, idx+1);
		start_distance = parse(1);
		start_record += num-1;
		strcpy(records_work, records[start_record]);
		stop_seconds = parse(3);
		strcpy(records_work, idx+1);
		stop_distance = parse(1);
		pace = stop_seconds-start_seconds;
		pace /= stop_distance-start_distance;
		pace /= 60;
		if (pace > max) max = pace;
		if (pace < min) min = pace;
		printf("\navg. pace over this ");
		printf("%2.3f mile stretch was ", stop_distance-start_distance);
		printf("%2.3f min. per mile", pace);
		start_record += 1;
	}
	printf("\n\nfastest avg. pace %2.3f min. per mile", min);
	printf("\nslowest avg. pace %2.3f min. per mile\n", max);
	exit(0);
}

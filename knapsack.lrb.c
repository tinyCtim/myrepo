
// knapsack.lrb.c - 7/25/20

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
 *
 * This program determines which of the 27 people to pick so that their
 * total weight is under 125. / 2 * 27 * .5 pounds (total weight if about
 * half the people get on an elevator) and the total amount of money on
 * them is maximum.
 *
 * Compare this to the recursive program knapsack.c, which takes much less
 * time to run. Richard Bellman coined the term dynamic programming, the
 * approach used in this other solution.
 *
 */

// https://www.facebook.com/groups/299317782048/permalink/10158775601082049/
// https://primepuzzle.com/not.just.tiny.c/knapsack.lrb.c
// https://primepuzzle.com/not.just.tiny.c/knapsack.c 

// pn is converted to binary and if a 1 is encountered, the corresponding
// element in the array is accumulated. the sum is returned.
int total(int pn, int array[])
{
	int binaryNum[27];
	int i = 0;
	while (pn > 0) {
		// storing remainder in binary array
		binaryNum[i] = pn % 2;
		pn /= 2;
		i++;
		}
	int tot = 0;
	for (int j = i - 1; j >= 0; j--) {
		tot += array[j] * binaryNum[j];
		}
	return tot;
}

// load the current date and time into supplied buff
char *cdate(char *buff)
{
	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = localtime(&rawtime);
	sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", \
	  info->tm_year-100 + 2000, info->tm_mon+1, \
	  info->tm_mday, info->tm_hour, info->tm_min, \
	  info->tm_sec);
	return buff;
}

int main(void)
{
	printf("\nknapsack.lrb.c - 7/25/20\n");
	char datebuff[20];
	cdate(datebuff); // get the current date and time
	printf("\n%s\n", datebuff + 11);
	int val[27], wt[27];
	int i, n = 27;
	int pn = pow(2, n); // up to 27 people can get on elevator
	time_t t;
	srand((unsigned) time(&t)); // seed random number generator
	for (i = 0; i < n; i++) {
		// random value in wallet / purse is ~ $50 / 2
		val[i] = rand() % 50;
		// random weight of person is ~ 125 / 2 lbs
		wt[i] = rand() % 125;
		}
	int W = 125. / 2 * n * .5; // ~ 50% of the people will get on elevator
	printf("\nmax weight %d\n", W);
	int max = 0, maxi, x, y, cwt;
	for (i = 0; i < pn; i++) {
		if ((x = total(i, wt)) <= W) {
			if ((y = total(i, val)) > max) {
				cwt = x; max = y; maxi = i;
				}
			}
		}
	printf("\ncumulative dollar value %d, cumulative weight %d\n", \
		max, cwt);
	int c, k, peeps = 0;
	for (c = 0; c < n; c++) {
		k = maxi >> c;
		if (k & 1) {
			printf("\npick person %d (dollar value %d weight %d)", \
				c + 1, val[c], wt[c]);
			peeps++;
			}
		}
	printf("\n\n%d people rode the elevator.\n", peeps);
	cdate(datebuff);
	printf("\n%s\n", datebuff + 11);
	return 0;
}

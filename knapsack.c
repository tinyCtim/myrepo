
// knapsack.c - 7/25/20

// from https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

// lrb

/*
 *
 * From 27 people weighing random weights (0 .. 125 lbs) and having random
 * amounts of money (0 .. $50) some are selected to maximize the total
 * amount of money while keeping the total weight under 125. / 2 * 27 * .5
 * pounds (total weight if about half the people get on).
 *
 * Compare this to the non-recursive approach in knapsack.lrb.c.
 *
 */

// https://www.facebook.com/groups/299317782048/permalink/10158775601082049/
// https://primepuzzle.com/not.just.tiny.c/knapsack.lrb.c
// https://primepuzzle.com/not.just.tiny.c/knapsack.c 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// load current date and time into supplied buff
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

int max(int a, int b) {
	return (a > b) ? a : b;
}

// return the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
	// base case
	if (n == 0 || W == 0) return 0;
	// if weight of the nth item is more than
	// knapsack capacity W then this item cannot
	// be included in the optimal solution
	if (wt[n - 1] > W) return knapSack(W, wt, val, n - 1);
	// return the maximum of two cases:
	// (1) nth item included (2) nth item not included
	else return max(val[n - 1] + knapSack(W - wt[n - 1], wt, val, n - 1), \
		knapSack(W, wt, val, n - 1));
}

int main(void)
{
	printf("\nknapsack.c - 7/25/20\n");
	char datebuff[20];
	cdate(datebuff); // get the current date and time
	printf("\n%s\n", datebuff + 11);
	int val[27], wt[27];
	int i, n = 27;
	time_t t;
	srand((unsigned) time(&t));
	for (i = 0; i < n; i++) {
		// random value in wallet / purse is ~ $50 / 2
		val[i] = rand() % 50;
		// random weight of person is ~ 125 / 2 lbs
		wt[i] = rand() % 125;
		}
	int W = 125. / 2 * n * .5; // ~ 50% of the people will get on elevator
	printf("\nmax weight %d\n", W);
	printf("\ndollar value is %d", knapSack(W, wt, val, n));
	cdate(datebuff);
	printf("\n\n%s\n", datebuff + 11);
	return 0;
}

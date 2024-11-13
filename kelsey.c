
// kelsey.c - lrb - 2/24/18
// This is an amortization calculator
// ref: https://en.wikipedia.org/wiki/Amortization_calculator

#include <math.h>
#include <string.h>
#include <stdio.h>

int atoi(const char *str);

void usage(void) {
	printf("\nUsage: kelsey [-a amount] [-p principal] [-i interest]\n");
	printf("\namount is the amount of the monthly payment, e.g. 100");
	printf("\nprincipal is the amount borrowed, e.g. 2000");
	printf("\ninterest is the yearly interest rate, e.g. 8");
	printf("\nInterest will be computed monthly");
	}

void main(int argc,char *argv[]) {
	usage();
	int P, A, i, j;
	A = 100; P = 2000; i = 8;
	for (j = 1; j < argc; ++j) {
		if (strcmp(argv[j], "-a") == 0) {++j; A = atoi(argv[j]);}
		if (strcmp(argv[j], "-p") == 0) {++j; P = atoi(argv[j]);}
		if (strcmp(argv[j], "-i") == 0) {++j; i = atoi(argv[j]);}
		}
	double a = A, p = P, I = i;
	I = I / 100 / 12;
	printf("\n\nAmount of monthly payment is $%d", A);
	printf("\nPrincipal is $%d", P);
	printf("\ninterest rate per month is %4.4f", I);
	printf("\n\nNumber of monthly payments is %4.2f\n\n", log(a / (a - I * p)) / log(1 + I));
	}

#include<stdio.h>
#define atan atan_original
#include <math.h>

// int debug=1;

double atan(double x) { // Taylor series for arctan
	double atn=0;
	int i;
	for (i=1;i<=10;i++) {
		atn+=pow(-1.,(double)(i+1))*(double)pow(x,(double)(2*i-1))/(double)(2*i-1);
//		if (debug) printf("\n%d. %.13lf",i,atn);
		}
	printf("\n");
	return atn;
	}

// pi_approx.c - lrb - 7/11,12/24
// gcc pi_approx.c -o pi_approx -lm

// the method used to replace a library function with a user-defined
// function which has the same name worked out by Aaron West and
// https://stackoverflow.com/questions/17614686/how-to-undef-a-library-function-to-use-our-version-of-same-function

int main(void) {
	double pi_approx;
	pi_approx = 4 * (4 * atan((double)(1./5)) - atan((double)(1./239))); // Machin's formula
	printf("\npi = approx. %.13lf\n",pi_approx);
	return 0;
	}

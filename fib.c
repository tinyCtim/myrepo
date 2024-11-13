
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// 6/22/21 - lrb - approximates phi using Fibonacci number ratios

long int fib (long int i) {
	if (i>1) return(fib(i-1)+fib(i-2));
	return(1);
	}

void main () {
	long int i,fib1,fib2;
	printf("\nenter an integer > 1 and < 46 : ");
	scanf("%li",&i);
	fib2=fib(i);fib1=fib(i-1);
	printf("\nfib(%li) = %li\n",i,fib2);
	printf("\nfib(%li) = %li\n",i-1,fib1);
	printf("\nratio of these two numbers = %20.19f\n",(double)fib2/(double)fib1);
	printf("\nphi = %20.19f\n",(sqrt(5)+1)/2);
	}


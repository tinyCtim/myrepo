
// https://c-program-example.com/2012/01/c-program-to-implement-integration

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Program to perform definite integral of a function between two
boundary limits input by user. Feel free to use and modify it, but
please do not remove this comment.
*/

// https://www.desmos.com/calculator/g8y6ycwrg1
// https://www.desmos.com/calculator/wu2uvetdqp

#define N pow(10, 8)

void help(void)
{
	printf("\ncase 1 : // Amy - http://primepuzzle.com/tunxis/4.11.20.html");
	printf("\n y = pow(x, 3) - pow(x, 4)");
	printf("\ncase 2 : // ?");
	printf("\n y = 4 * x + 5 * pow(x, 2)");
	printf("\ncase 3 : // Joseph - Problem 16 Section 5.1 - http://primepuzzle.com/tunxis/4.20.20.html");
	printf("\n y = pow(x, 2) * exp(x)");
	printf("\ncase 4 : // Sergio - http://primepuzzle.com/tunxis/4.23.20.html");
	printf("\n y = -pow(x, 2) + 3 * x - 2");
	printf("\ncase 5 : // normal distribution");
	printf("\n y = 1/sqrt(2*3.14159)*exp(-.5*x*x)");
	printf("\ncase 6 : // charles hilton");
	printf("\n y = 1 / (1 + x * x)");
}

int main(void)
{
	help();
	double dx, y, x, a, b, sum = 0;
	int bi;
	printf("\n\nintegration.amy.try.c - 4/23/20, 6/28,29/24 - lrb\n");
	printf("\nThis program integrates a function between two boundary limits.\n");
	printf("\nEnter a, the lower bound: ");scanf("%lf", &a);
	printf("\nEnter b, the upper bound: ");scanf("%lf", &b);
	if (a >= b)
	{
		printf("\na must be < b\n");
		exit(1);
	}
	dx = (b - a) / N;
	int num;
	printf("\nEnter a number in [1..9] ");
	scanf("%d", &num);
	for (x = a;x <= b;x += dx)
	{
		switch(num)
		{
		case 1 : // Amy - http://primepuzzle.com/tunxis/4.11.20.html
		y = pow(x, 3) - pow(x, 4);break;
		case 2 :
		y = 4 * x + 5 * pow(x, 2);break;
		case 3 : // Joseph - Problem 16 Section 5.1 - http://primepuzzle.com/tunxis/4.20.20.html
		y = pow(x, 2) * exp(x);break;
		case 4 : // Sergio - http://primepuzzle.com/tunxis/4.23.20.html
		y = -pow(x, 2) + 3 * x - 2;break;
		case 5 : // normal distribution
		y = 1 / sqrt(2 * 3.14159) * exp(-1 * .5 * x * x);break;
		case 6 :
		y = 1 / (1 + x * x);break;;

		case 100 :
		printf("\ne = %.8lf\n", exp(1));exit(0);
		case 101 :
		bi = (int)b;
		printf("\natan(%d) = %.8lf\n", bi, atan(b));exit(0);
		
		default :
		printf("\nnot implemented yet ...\n");exit(1);
		}
	sum += y * dx;
	}
	printf("\nThe value of the integral is about: %.8lf\n", sum);
	return 0;
}



/*
5/15/20 - lrb

https://www.facebook.com/groups/299317782048/permalink/10158521588032049/

https://financeformulas.net/Future-Value-of-Annuity-Continuous-Compounding.html

http://primepuzzle.com/not.just.tiny.c/future.value.annuity.cont.comp.1.png
http://primepuzzle.com/not.just.tiny.c/future.value.annuity.cont.comp.2.png
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
This program computes how much you have to save and deposit each year in
order to have a desired amount of money after a specified number of
years given a specified annual interest rate. Your money will be
compounded continuously.
*/

// gcc -lm -o may.2020.challenge may.2020.challenge.c

int main(void)
{
	printf("\nmay.2020.challenge.c\n");
	float r, g;
	int y;
	printf("\nEnter annual interest rate (e.g. 0.04125) : ");
	scanf("%f", &r);
	printf("\nEnter years (e.g. 5) : ");
	scanf("%d", &y);
	printf("\nEnter goal (e.g. 25000) : ");
	scanf("%f", &g);
	printf("\ngoal = %.2f rate = %.5f years = %d\n", g, r, y);
	printf("\nyearly deposit = %.2f\n", g * (1 - exp(r)) / (1 - exp(r*y)));
	exit(0);
}

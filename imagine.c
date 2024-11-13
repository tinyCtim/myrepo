
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

/*

generates the sequence {1 0 -1 0 1 0 -1 0 ...}

imagine.c - 11/1/20 - lrb

two ways to generate this sequence are used. the 1st one uses the sine
function. the 2nd one uses the function imagine. the name of this
program comes from the fact that Euler's formula can be used to show
that

sin((n+1)pi/2) = ((i^n) * (1 + (-1)^n)) / 2

where i is the imaginary unit (i^2 = -1)

if n is 0 or 4 or 8 etc. the above function is 1
if n is 2 or 6 or 10 etc. the above function is -1
and if n is 1 or 3 or 5 etc. the 0 factor causes the function to be 0

*/

/*

https://www.facebook.com/groups/299317782048/permalink/10159062601902049/

*/

int imagine(int n) {
	if ((n + 1) % 4 == 1) return 1;
	if ((n + 1) % 2 == 0) return 0;
	return -1;
	}

void main(void) {
	printf("\nimagine.c - lrb - 11/1/20\n");
	float pi = M_PI;
	int n, result;
	float foo;
	printf("\nEnter n (0, 1, ...) ");
	scanf("%d", &n);
	foo = sin((n + 1) * pi / 2);
	if ((abs(foo)) == 0) foo = 0; // to get rid of -0
	printf("\n%1.0f", foo);
	printf("\n%d\n", imagine(n));
	}

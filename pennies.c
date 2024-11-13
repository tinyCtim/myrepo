// pennies.c - 1/22/24 - lrb
// compute and display dollar value of coins from top of building to top of spire 

#include <stdio.h>
#include <stdlib.h>

int main () {
	float p, b, t, v;
	p = 1.52 / 1000; // thickness of coin in meters
	t = 443; // height to top of spire in meters
	b = 380; // height to top of building in meters
	v = .01; // value of coin in dollars (i.e. a penny) 
	printf("\nvalue = %4.3f\n", v * (t - b) / p);
	exit(0);
}

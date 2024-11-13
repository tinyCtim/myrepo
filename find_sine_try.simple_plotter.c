#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
find_sine_try.c - 9/17,18,22,23,26,29/23 - lrb

ref: september 2023 exercise on not just tinyC programming group on
Facebook

given (xmax, ymax), the coordinates of the maximum, and (xmin, ymin),
the coordinates of the neighboring minimum, find the y = a sin(f(x + p))
+ d that passes thru these points

this version runs a Python plotter script and feeds it the function
*/

int main()
{
	float xmax, xmin, ymax, ymin;
	float a, d, f, p; // amplitude, vertical displacement, frequency, horizontal phase shift
	float t; // period
	float x; // work variable for phase calculation
	float y;
	printf("\nenter xmax, ymax, xmin, ymin, e.g. -1 5 3 -1 : ");
	scanf("%f %f %f %f", &xmax, &ymax, &xmin, &ymin);
	a = (ymax - ymin) / 2;
	d = ymax - a;
	t = 2 * (xmin - xmax); f = 2 * M_PI / t;
	// f * x = M_PI / 2; calculate at what x sin(f * x) is at max
	x = (M_PI / 2) / f; // solve the above for x
	p = x - xmax; // calculate phase
	char pycmd[50], tail[50];
	sprintf(tail, "%3.3f*sin(%3.3f*(x+%3.3f))+%3.3f\n", a, f, p, d);
	printf("\ny = %s", tail);
	strcpy(pycmd, "py simple_plotter.try.py ");
	strcat(pycmd, tail);
	system(pycmd);
	printf("\n");
	return 1;
}


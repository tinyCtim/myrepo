
// jim.mcclanahan.c - converted to C from YABASIC - 11/6,7,12,22/23

/*

lrb - mods per aaron west, vince otten. using double now, improved
decimal digit accuracy, changed for loop condition, eliminated all
output except final result, changed sscanf format specifier.

/*

/*

this program estimates the point on the x-axis which divides the area
under the curve y = -x(x-1) between x = 0 and x = 1 into the ratio 1:2.
you enter a number like .000001, to specify how accurate the estimate
should be. Two values are output: the left estimate and the right
estimate.

*/

#include <stdio.h>
#include <stdlib.h>

// ref: https://www.facebook.com/groups/299317782048/posts/10161491351157049

int main(void)
{
	double s, x1, x2, a1;
	FILE * fp;
	fp=fopen("jim.c.txt","w");

	char *buffer;
	size_t bufsize = 32;
	size_t characters;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if( buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(1);
		}

	printf("\nEnter s, e.g. .00001 : ");
	characters = getline(&buffer,&bufsize,stdin);
	sscanf(buffer, "%lf", &s);

	x2 = 1 - s;
	for (x1 = s; x2 > x1; x1 += s) {
		a1 = s * (-x1 * (x1 - 1));
		x2 = x2 - 2 * a1 / (-x2 * (x2 - 1));
		}

	printf("\nleft estimate %.10lf, right estimate %.10lf\n\n", x2, x1);
	fprintf(fp, "\nleft estimate %.10lf, right estimate %.10lf\n\n", x2, x1);
	fclose(fp);
	return(0);
}


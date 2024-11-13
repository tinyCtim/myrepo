#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// 5/27/22 - this version uses data output by xa.c
// ref: http://primepuzzle.com/not.just.tiny.c/xa.c

// https://www.emathhelp.net/en/calculators/calculus-2/arc-length-calculus-calculator/?ft=x&f=x%5E2&a=1&b=2

// june.22.c - lrb
// ref: https://www.facebook.com/groups/299317782048/posts/10160299740482049/

// Estimate the length of a curve based on x,y pairs on the curve.

double dist(double x1,double y1,double x2,double y2) {
 return pow( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1),.5 );
 }

int main(void) {

 printf("\njune.22b.c - lrb\n");

 double arr[11][2] =

// xa.c - 5/27/22 - lrb

{
{1.000000,1.000000},
{1.100000,1.210000},
{1.200000,1.440000},
{1.300000,1.690000},
{1.400000,1.960000},
{1.500000,2.250000},
{1.600000,2.560000},
{1.700000,2.890000},
{1.800000,3.240000},
{1.900000,3.610000},
{2.000000,4.000000}
};

 double length = 0;
 int i;
 int n = 11;
 int verbose;
 verbose = 1;
 double work;

 for (i=0;i<n-1;i++) {
  work = dist(arr[i][0],arr[i][1],arr[i+1][0],arr[i+1][1]);
  length += work;
  if (verbose==1) printf("\ni = %d dist = %f length = %f",i,work,length);
  }

 printf("\n");
 printf("\ncurve length = ~ %f",length);
 printf("\n");
 exit(0);

 }


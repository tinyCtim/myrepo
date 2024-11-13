#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// june.22c.c - lrb

// Estimate the length of a curve defined by a function

double fn(double x) {
 return pow(x,2);
 }

double dist(double x1,double y1,double x2,double y2) {
 return pow( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1),.5 );
 }

int main(void) {

 printf("\njune.22c.c - lrb\n");

 double length = 0;
 int verbose = 0;
 double x = 1;
 double delta = .000001; // 6/3/22
 
 while (x<2-delta) { // 6/3/22
  length += dist(x,fn(x),x+delta,fn(x+delta));
  if (verbose==1) printf("\n%1.6f,%1.6f,length = %1.6f",x,x+delta,length); // 6/3/22
  x += delta;
  }

 printf("\n\ncurve length = ~ %f\n",length);
 exit(0);

 }

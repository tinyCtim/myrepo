#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// june.22.c - lrb
// ref: https://www.facebook.com/groups/299317782048/posts/10160299740482049/

float dist(float x1,float y1,float x2,float y2) {
 return pow( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1),.5 );
 }

int main(void) {

 printf("\njune.22.c - lrb\n");

 float arr[13][2] =

{
{0.000000,0.000000},
{0.062500,0.250000},
{0.187500,0.500000},
{0.250000,0.583333},
{0.375000,0.750000},
{0.500000,0.833333},
{0.750000,0.833333},
{0.812500,0.750000},
{0.833333,0.500000},
{0.875000,0.250000},
{0.750000,0.166667},
{0.500000,0.083333},
{0.250000,0.041667}
};

 float length = 0;
 int i;
 int n = 13;
 int verbose;
 verbose = 0;

 for (i=0;i<n-1;i++) {
  length += dist(arr[i][0],arr[i][1],arr[i+1][0],arr[i+1][1]);
  if (verbose==1) printf("\nlength = %f",length);
  }

 length += dist(arr[n-1][0],arr[n-1][1],arr[0][0],arr[0][1]);
 if (verbose==1) printf("\nlength = %f",length);

 printf("\n");
 printf("\ncurve length = ~ %f",length);
 printf("\n");
 exit(0);

 }


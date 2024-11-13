
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// dandelion.1.c - lrb - 4/14/22
// gcc dandelion.1.c -o dandelion.1.exe

int main() {

 float cumarr[20] = {
  0.006738, 0.040428, 0.124652, 0.265027, 0.440495,
  0.615963, 0.762186, 0.866631, 0.931909, 0.968175,
  0.986308, 0.994550, 0.997985, 0.999305, 0.999777,
  0.999934, 0.999983, 0.999998
  };

 time_t t;
 srand((unsigned) time(&t));
 int rn;
 float frn;
 float tot = 0;
 int k;

 printf("\ndandelion.1.c - lrb - 4/14/22\n\n");

 for (int i=0; i<20; ++i) {
  rn = rand()%100;
  frn = rn / 100.;
  k=0;
  while (frn>cumarr[k]) ++k;
  printf("%d ",k);tot+=k;
  }

 printf("\n");
 printf("\naverage number of dandelions was %2.1f\n",tot/20);

 }


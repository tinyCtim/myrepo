
// https://stackoverflow.com/questions/1057621/calculation-of-poisson-distribution-in-c

// lrb - 4/13/22
// notes to self: don't forget stdlib.h, make array size big enuf
// 4/15/22
// fb: https://www.facebook.com/groups/299317782048/posts/10160229762057049/

// gcc dandelion.c -o dandelion -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

double poisson( int k, double mean ) {
 double p = exp(-mean);
 double f = 1;
 for ( int i=0 ; i<k ; i++ ) f *= mean/(i+1);
 return p*f;
 }

int main(int argc, char **argv)
{
 typedef enum {false, true} bool;

 printf("\ndandelion.c - lrb - 4/16/22\n");
 printf("\nUsage: dandelion [-d] [-m mean]\n\n");

 bool debug = false;
 int lambda = 5;

 if (argc > 1) {
  for (int i = 1;i < argc;i++) {
   if (strcmp(argv[i],"-m") == 0) lambda = atoi(argv[++i]);
   if (strcmp(argv[i],"-d") == 0) debug = true;
   }
  }

 int k = 0;
 double prob;
 double cumulative;
 prob = cumulative = 0;
 double cumarr[200];
 while ( k <= 200 ) {
  prob = poisson(k, (double)lambda);
  cumulative += prob;
  // note trailing space in format spec
  if (debug == true) {
   printf("%d %2.2f %2.2f ", k, prob, cumulative);
   if (k * (k%8==0)) printf("\n");
  }
  cumarr[k] = cumulative;
  ++k;
  }
 printf("\n\n");
 time_t t;
 srand((unsigned) time(&t));
 int rn;
 float tot = 0;
 double frn;
 for (int i=0; i<20; ++i) {
  rn = rand()%100;
  frn = rn/100.;
  k = 0;
  while (frn>cumarr[k]) ++k;
  printf("%d ", k);tot += k;
  }
 printf("\n");
 printf("\naverage number of dandelions was %3.1f\n", tot/20);
}


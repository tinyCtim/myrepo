#include<stdio.h>
#include<stdlib.h>

/*

candy.c - 10/23/20 - lrb

Candy bars cost $1. This program displays a chart that shows how many
candy bars you can buy if you have b dollars and get can get another
candy bar with w wrappers.

*/

void main(void) {
 printf("\ncandy.c - lrb - 10/23/20\n");
 int b, w;
 printf("\n       ");
 for (b = 5; b <= 30; ++b) {
  printf(" $%3d", b);
  }
 printf("\n");
 for (w = 2; w <= 15; ++w) {
  printf("\nw = %2d  ", w);
  for (b = 5; b <= 30; ++b) {
   printf(" %3d ", b + (b - 1) / (w - 1));
   }
  }
 printf("\n");
 }

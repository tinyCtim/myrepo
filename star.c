
/*
This program generates and displays p-point skip-s stars.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char ar[80][80];

void plot (double xo,double yo,double xn,double yn) {

 double x,y,b,m,inc;int i,j;

 if (abs(xn-xo)<1) {
  inc=yo<yn?1:-1;
  for (y=yo;;y+=inc) {
   if (abs(y-yn)<.1) break;
   j=39+y;i=39+xo;
   ar[j][i]='*';
   }}
 else {
  m=(yn-yo)/(xn-xo);b=yn-m*xn;
  inc=xn<xo?-.1:.1;
  for (x=xo;;x+=inc) {
   if (abs(x-xn)<.1) break;
   y=m*x+b;j=39+y;i=39+x;
   ar[j][i]='*';

 }}}

int main(int argc,char *argv[]) {

 int i,j,skip,points;double xo,yo,xn,yn,degrees,thetao,thetan;

 points=17;skip=5;

 for (i=1;i<argc;++i) {
  if (strcmp(argv[i],"-p")==0) {++i;points=atoi(argv[i]);}
  if (strcmp(argv[i],"-s")==0) {++i;skip=atoi(argv[i]);}
  }

 degrees=360.0/points;

 for (i=0;i<=79;++i) for (j=0;j<=79;++j) ar[i][j]=' ';

 printf("\nstar.c - lrb - 1/21/18\n");
 printf("\nUsage: ./star {-p points}{ -s skip}\n");
 printf("\n%d-point skip-%d star\n\n",points,skip);

 for (i=0;i<=points-1;++i) {
  thetao=M_PI/180*(skip+1)*i*degrees;thetan=M_PI/180*(skip+1)*(i+1)*degrees;
  xo=35*cos(thetao);yo=35*sin(thetao);xn=35*cos(thetan);yn=35*sin(thetan);
  plot(xo,yo,xn,yn);
  }

 for (j=79;j>=0;--j) {
  printf("    ");
  for (i=0;i<=79;++i) {printf("%c ",ar[j][i]);}
  printf("\n");
  }

 printf("\n");exit(0);

 }


#include <stdio.h>
#include <stdlib.h>

// chapter.2.c
// 2/28/20 - lrb
// ref: http://primepuzzle.com/lee-bradley/mini.challenges.html

// to compile

// gcc chapter.2.c -o chapter.2.exe (Windows)
// gcc chapter.2.c -o chapter.2 (Linux)

// to run

// chapter.2.exe (Windows)
// ./chapter.2 (Linux)

int main(void) {
 printf("\nchapter.2.c - 2/28/20 - lrb\n");
 int n,i;
 int minutes,seconds;
 int total_seconds=0;
 int min=999,max=0;
 int total;
 int avg_min,avg_sec;
 printf("\nenter n : ");
 scanf("%d",&n);
 for (i=1;i<=n;++i) {
  printf("\nenter minutes : ");
  scanf("%d",&minutes);
  printf("\nenter seconds : ");
  scanf("%d",&seconds);
  total=minutes*60+seconds;
  if (total<min) min=total;
  if (total>max) max=total;
  total_seconds+=total;
  } // end for
 total_seconds/=n;
 avg_min=total_seconds/60;
 avg_sec=total_seconds%60;
 printf("\nfastest pace = %d:%d\n",min/60,min%60);
 printf("\nslowest pace = %d:%d\n",max/60,max%60);
 printf("\naverage pace = %d:%d\n",avg_min,avg_sec);
 exit(0);
 }

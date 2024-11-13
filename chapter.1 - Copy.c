#include <stdio.h>
#include <stdlib.h>

// chapter.1.c
// 2/27/20 - lrb
// ref: http://primepuzzle.com/lee-bradley/mini.challenges.html

// to compile

// gcc chapter.1.c -o chapter.1.exe (Windows)
// gcc chapter.1.c -o chapter.1 (Linux)

// to run

// chapter.1.exe (Windows)
// ./chapter.1 (Linux)

int main(void) {
 printf("\nchapter.1.c - 2/27/20 - lrb\n");
 int minutes,seconds;
 int total_seconds;
 printf("\nenter total seconds : ");
 scanf("%d",&total_seconds);
 if (total_seconds>=1500) {printf("\ntotal seconds must be < 1500\n");exit(1);}
 minutes=total_seconds/60;
 seconds=total_seconds%60;
 printf("\nminutes = %d\n",minutes);
 printf("\nseconds = %d\n",seconds);
 exit(0);
 }

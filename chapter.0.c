#include <stdio.h>
#include <stdlib.h>

// chapter.0.c
// 2/26/20 - lrb
// ref: http://primepuzzle.com/lee-bradley/mini.challenges.html

// to compile

// gcc chapter.0.c -o chapter.0.exe (Windows)
// gcc chapter.0.c -o chapter.0 (Linux)

// to run

// chapter.0.exe (Windows)
// ./chapter.0 (Linux)

int main(void) {
 printf("\nchapter.0.c - 2/26/20 - lrb\n");
 int minutes,seconds;
 int total_seconds;
 printf("\nenter minutes : ");
 scanf("%d",&minutes);
 printf("\nenter seconds : ");
 scanf("%d",&seconds);
 total_seconds=60*minutes+seconds;
 printf("\ntotal seconds = %d\n",total_seconds);
 exit(0);
 }

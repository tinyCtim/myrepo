#include <stdio.h>
#include <stdlib.h>

// gus.c - 11/4/22 - lrb

void main(void) {
 printf("\nEnter a grade, e.g. 87 or 72 or 95 etc. ");
 int grade; // declare the integer variable grade
 scanf("%d",&grade); // gets a number from the keyboard and saves it in grade
 if (grade < 60) printf("F");
 else if (grade < 70) printf("D");
 else if (grade < 80) printf("C");
 else if (grade < 90) printf("B");
 else printf("A");
 printf("\n");
 }

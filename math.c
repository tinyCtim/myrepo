#include<stdio.h>
#include<stdlib.h>

// math.c - 1/7/9 - lrb - from amy merritt

// (ab)^2 = cab   what's c?

int main() {
  printf("math.c - lrb - 1/7/9");
  int a,b,c;
  for (a=1;a<10;++a) {
    for (b=0;b<10;++b) {
      for (c=1;c<10;++c) {
        if (100*a*a+20*a*b+b*b==100*c+10*a+b) {
          printf("\na = %d b = %d c = %d\n",a,b,c);
          printf("100*a*a+20*a*b+b*b = ");
          printf("%d + %d + %d = ",100*a*a,20*a*b,b*b);
          printf("%d",100*a*a+20*a*b+b*b);
          printf(" = 100*c+10*a+b = ");
          printf("%d + %d + %d",100*c,10*a,b);
          }
        }
      }
    }
    printf("\n");
  }


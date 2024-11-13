#include<stdio.h>
#include<stdlib.h>

// ABCDE x A = EEEEEE

int a,b,c,d,e;

void output(void) {
 printf("\n%d%d%d%d%d*%d=%d%d%d%d%d\n",a,b,c,d,e,a,e,e,e,e,e,e);
 }

int formula(void) {
 if ((a==b||a==c||a==d||a==e||b==c||b==d||b==e||c==d||c==e||d==e)) return 0;
 return ((e+10*d+100*c+1000*b+10000*a)*a)==(e+10*e+100*e+1000*e+10000*e+100000*e);
 }

int main(void) {
 for (a=1;a<10;a=a+1) {
 for (b=1;b<10;b=b+1) {
 for (c=1;c<10;c=c+1) {
 for (d=1;d<10;d=d+1) {
 for (e=1;e<10;e=e+1) {
 if (formula()==1) output();
 }
 if (formula()==1) output();
 }
 if (formula()==1) output();
 }
 if (formula()==1) output();
 }
 if (formula()==1) output();
 }
 }


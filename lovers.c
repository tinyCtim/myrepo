
/* lovers.c - tct - 2/8/15 */

/* motivated by Nhung Blaschke's C++ assignment */

/* http://primepuzzle.com/tc/lovers.c */
/* http://primepuzzle.com/karen_armillei/lovers.jpg */

/* B. Nicolò I. Paganini discovered the second smallest */
/* pair when he was 16. */

#include<stdio.h>

int sumpdiv(int m) { /* sum of proper divisors */
 int o,s;s=1;
 for (o=2;o<=m/2;++o) {
  if (m%o==0) s+=o;
  }
 return s;
 }

int main () {
 int i,j,k,l,w;
 printf("lovers.c - 2/8/15 - tct\n");
 printf("enter a lower limit between 1 and 1000000 : ");w=scanf("%d",&i);printf("\n");
 printf("enter an upper limit between 1 and 1000000 : ");w=scanf("%d",&j);printf("\n");
 for (k=i;k<=j;++k) {
  if (k%1000==0) printf("%c",'.');
  if (sumpdiv(l=sumpdiv(k))==k) {
   if (k<l) {
    printf("\n%d and %d are lovers.\n",k,l);       
 }}}}



#include<stdio.h>

void add(int *a,int *b,int d) {
 int i,c,w;
 c=0;
 for (i=0;i<=d;++i) {
  w=a[d-i]+b[d-i]+c;a[d-i]=w%10;c=w/10;
 }}

/*
subtract computes the difference of a and b and puts it in a.
It destroys the contents of b. 9's complement arithmetic is used.
*/

void subtract(int *a,int *b,int d) {
 int i;
 for (i=0;i<=d;++i) b[i]=9-b[i];
 add(a,b,d);
 b[d]=1;for (i=0;i<d;++i) b[i]=0;
 add(a,b,d);
 }

/*
multiply computes the product of m and a and puts it in a.
*/

void multiply(int *a,int m,int d) {
 int i,c,w;
 c=0;
 for (i=0;i<=d;++i) {
  w=a[d-i]*m+c;a[d-i]=w%10;c=w/10;
 }}

char *itoa(int n) {
 static char retbuf[25];
 sprintf(retbuf,"%d",n);
 return retbuf;
 }

int main() {
 printf("multseq.c - 5/16/12 - tct\n");
 int a[10000],b[10000],i,j,d,n,w;
 char *p;
 char q[20];
 printf("enter a number < 19999 : ");if ((w=scanf("%d",&n)));printf("\n");
 d=(n+1)/2;
 for (i=0;i<=d;++i) b[i]=a[i]=0;
 a[d]=3;
 for (i=0;i<=n-2;++i) { /* compute 3^n */
  printf("%c",'.');if ((i+1)%40==0) printf("\n");
  multiply(a,3,d);
  }
 for (i=0;n>0;++i) {b[d-i]=n%10;n=n/10;}
 multiply(b,3,d); /* b now holds 3n */
 subtract(a,b,d); /* compute 3^n-3n */
 i=0;while (a[i]==0) ++i; /* don't print leading 0's */
 j=i;printf("%c",7);
 printf("\n\nHit '.' followed by Enter to continue");if ((w=scanf("%s",q)));
 printf("\n");printf("The %d digit value is\n\n",d-i+1);
 while (i<=d) {
  p=itoa(a[i]);
  printf("%s",p);++i;if ((i-j)%40==0) printf("\n");
  }
 printf("\n\n");
 return 1;
 }


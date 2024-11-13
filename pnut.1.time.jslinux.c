
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/*
The Prime Number Theorem says that n divided by the number of primes
less than n approaches the natural logarithm of n. This program counts
the number of primes <= n and displays this ratio and the natural
logarithm of n.
*/

int isprime(int number) { // returns 0 if number is composite, 1 if prime
 for (int i=2;i<number;++i) {
  if (number%i==0) return 0;
  } // end for
 return 1;
 }

void usage(void) {
 printf("\npnut.c - lrb - 2/19/20");
 printf("\n\nUsage: pnut -n number -v verbose");
 printf("\nwhere 2 <= n <= 2000000 and verbose = 0 or 1\n");
 exit(1);
 }

int main(int argc,char *argv[]) {
 time_t timer;
 char buffer[26];
 struct tm* tm_info;
 time(&timer);
 tm_info = localtime(&timer);
 printf("\nstart time ... ");
 strftime(buffer,26,"%Y-%m-%d %H:%M:%S",tm_info);
 puts(buffer);
 int lprime; // largest prime
 int verbose;
 if (argc!=5) usage();
 int i,n,ctr=1;
 for (i=1;i<argc;++i) {
  if (strcmp(argv[i],"-n")==0) {++i;n=atoi(argv[i]);}
  else if (strcmp(argv[i],"-v")==0) {++i;verbose=atoi(argv[i]);}
  else usage();
  }
 if (n<2) {printf("\nn is too small\n");exit(0);}
 if (n>2000000) {printf("\n n is too big\n");exit(0);}
 printf("\n");
 for (i=3;i<=n;i+=2) {
  if ((verbose==1)&&((i-1)%10000==0)) printf("%d ",(i-1)/10000);
  if ((verbose==1)&&((i-1)%100000==0)) printf("\n");
  if (isprime(i)==1) {
   ctr+=1;
   lprime=i;
   } // end if
  } // end for
 printf("\n\nlargest prime was %d\n",lprime);
 printf("\nn / # primes <= n = %d / %d = %3.11f\n",n,ctr,1.0*n/ctr);
 printf("\nln(%d) = %3.11f\n",n,log(n));
 time(&timer);
 tm_info = localtime(&timer);
 printf("\nend time ... ");
 strftime(buffer,26,"%Y-%m-%d %H:%M:%S",tm_info);
 puts(buffer);
 return 0;
 } // end main

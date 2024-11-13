
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// returns 0 if there are duplicate digits otherwise returns 1
int nodup(int x) {
 char buff[5];int i,j;
 snprintf(buff,5,"%04d",x);
 for (i=0;i<3;++i) {
  for (j=i+1;j<4;++j) {
   if (buff[i]==buff[j]) return 0;
  }}
 return 1;
 }

int score(int x,int y) { // count bulls and cows and return 10*b+c
 char s1[5],s2[5];int i,j,b,c;
 b=c=0;
 snprintf(s1,5,"%04d",x);snprintf(s2,5,"%04d",y);
 for (i=0;i<4;++i) {
  for (j=0;j<4;++j) {
   if (s1[i]==s2[j]) {
    if (i==j) ++b;else ++c;
    break;
  }}}
 return 10*b+c;
 }

int main(void) {

 printf("\nentropy.c - tct - 5/28/16");
 printf("\n\nThink of a 4-digit number. Use digits 0 thru 9.");
 printf("\nNo repeating digits.\n");

 int sc[41],gs,ar[5040],counts[5040][14];
 int scr,i,k,j,m,tries,maxm,b,c,ea[5040],e;
 double minm,entropy[5040],cnt;
 char s1[5];
 
// encode the scores : number of bulls is multiplied by 10 and added to
// number of cows

 sc[40]=0;sc[30]=1;sc[20]=2;sc[21]=3;sc[22]=4;sc[10]=5;sc[11]=6;
 sc[12]=7;sc[13]=8;sc[0]=9;sc[1]=10;sc[2]=11;sc[3]=12;sc[4]=13;

 m=-1;
 for (i=0123;i<=9876;++i) if (nodup(i)) ar[++m]=i;
 maxm=5039;tries=1;
 srand(time(NULL));
 gs=ar[rand()%5040];
 printf("\nCompare your number to my guess.");
 printf("\nCount the bulls (right digit, right position)");
 printf("\nand the cows (right digit, wrong position).\n");

 while (1) { // keep going till you have 4 bulls

  snprintf(s1,5,"%04d",gs);
  printf("\nMy guess for your 4-digit number is %s.",s1);
  printf("\nEnter two numbers, e.g. 0 2 for 0 bulls 2 cows : ");
  scanf("%d %d",&b,&c);scr=10*b+c;
  if (b==4) break;
  m=-1;
  for (i=0;i<=maxm;++i) {
   // reload array with numbers that have the right score
   if (scr==score(gs,ar[i])) ar[++m]=ar[i];
   }
  maxm=m; // update the upper limit of the array index
  minm=pow(10,9);
  for (i=0;i<=maxm;++i) {
   for (j=0;j<=13;++j) counts[i][j]=0;
   for (k=0;k<=maxm;++k) ++counts[i][sc[score(ar[k],ar[i])]];
   entropy[i]=0;
   // compute entropy
   for (j=0;j<=13;++j) {
    cnt=counts[i][j];if (cnt>1) entropy[i]+=cnt*log(cnt);
    }
   if (entropy[i]<=minm) {
    if (entropy[i]<minm) {e=0;minm=entropy[i];}
    ea[e++]=ar[i];
    }
  }
  gs=ea[rand()%e]; // pick a random one
  ++tries;

  }

 printf("\nIt took me %d",tries);
 printf((tries==1) ? " try!" : " tries!");
 printf("\nI am beyond awesome.\n");
 return 0;

 }


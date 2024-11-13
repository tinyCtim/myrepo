
#include<stdio.h>
#include<stdlib.h>

/*
A high school has a new principal. On
his first day he had his students
perform an opening day ceremony.
There are 1000 lockers and 1000
students in the school. The principal
asks the first student to go to every
locker and open it. Then he asks the
second student to go to every second
locker (even #) and close it. He has
the third student go to every third
locker and open it if it's closed and
close it if it's open. He has the fourth
student do this to every fourth locker
and so on. After the process is completed
with the 1000th student how many lockers
are open?
*/

void main() {

 printf("\nalanna3.c - tct - 9/30/2016, 10/15/24\n\n");
 // locker array, index, locker number, total
 int la[1001],i,lm,tot=0;
 for (i=1;i<=1000;i++) {la[i]=0;}

 for (lm=1;lm<=1000;++lm) {
  for (i=lm;i<=1000;i=i+lm) {
   la[i]=1-la[i]; // toggle locker state
   }
  }

 for (i=1;i<=1000;++i) {
  if (la[i]==1) { // if open, display and tally
   printf("%d ",i);++tot;
   if (i%10==0) printf("\n");
   }
  }

 printf("\n\n%d lockers are open.\n",tot);

 }


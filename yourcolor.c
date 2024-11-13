// https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

#include <stdio.h>
#include <stdlib.h>

// yourcolor.c - lrb - 1/31/23
// fixed by adding a null to end of c array - 6/6/23

int main ()

{

 char c3[3];
 char c1,c10,c100;
 int i=0;
 char c[12]="\033[38;5;xxxm\0";
 printf("\n");

 while (i<256) {

  c100='0'+i/100;
  c10='0'+i/10%10;
  c1='0'+i%10;
  c3[0]=c100;c3[1]=c10;c3[2]=c1;
  c[7]=c3[0];
  c[8]=c3[1];
  c[9]=c3[2];
  printf("%s%d ",c,i);
  if (i*(i%16==0)) printf("\n");
  ++i;

  }

 printf("\n\n");

 return(0);

}

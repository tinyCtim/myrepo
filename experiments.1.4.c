
#include<stdio.h>
#include<stdlib.h>

char c1[12]="\033[38;5;208m"; //orange
char c2[12]="\033[38;5;xxxm"; //unknown 1 e.g. 209
char c3[12]="\033[38;5;xxxm"; //unknown 2 e.g. 210
char c4[12]="\033[38;5;xxxm"; //unknown 3 e.g. 211

// https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

char r[10]="\033[0m";     // reset

// experiments.1.4.c - 1/26/23 - C. Bradley

/*
This program prints orange and 3 other as yet unknown colors
*/

// to compile: gcc experiments.1.4.c -o experiments.1.4

// 1/30/23 - Editor's Comment Area:

int main()
{

printf("\nexperiments.1.4 - ceb\n" );

char s2[3],s3[3],s4[3];   // s2 = 2nd color, s3 = 3rd color, s4 = 4th color

printf("\nEnter 3-digit decimal number e.g. 209  : ");
scanf("%s",s2);
printf("\nEnter 3-digit decimal number e.g. 210  : ");
scanf("%s",s3);
printf("\nEnter 3-digit decimal number e.g. 211  : ");
scanf("%s",s4);

c2[7]=s2[0];
c2[8]=s2[1];
c2[9]=s2[2];

c3[7]=s3[0];
c3[8]=s3[1];
c3[9]=s3[2];

c4[7]=s4[0];
c4[8]=s4[1];
c4[9]=s4[2];

printf("\n");
printf("\n %scolor 1 %s %scolor 2 %s %scolor 3 %s %scolor 4 %s ",c1,r,c2,r,c3,r,c4,r);
printf("\n");

}


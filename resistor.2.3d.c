
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

char c0[10]="\033[1;30m"; // black
char c1[10]="\033[1;31m"; // red
char c2[10]="\033[1;32m"; // green
char c3[10]="\033[1;33m"; // yellow
char c4[10]="\033[1;34m"; // blue
char c5[10]="\033[1;35m"; // magenta
char c6[10]="\033[1;36m"; // cyan
char c7[10]="\033[1;37m"; // white

char c8[12]="\033[38;5;208m"; //orange

// https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

char c9[12]="\033[38;5;7m"; //silver
char ca[12]="\033[38;5;214m"; //gold
char cb[12]="\033[38;5;94m"; //brown
char cc[12]="\033[38;5;240m"; //grey
char cd[12]="\033[48;5;234m"; //black

char r[10]="\033[0m";     // reset

// resistor.2.3c - 1/24/23 - C. Bradley - With help from God

/*
 This program calculates Ohm values for electronic resistor components
 using input values for each of the four (4) bands of color.  A diagram will
 help the user to enter the appropriate number depending on what color(s)
 the user sees in each of the 4 bands.  The graphic will also explain the
 the different "functions" of each of the 4 bands. The final Ohm value
 will also display a + or - tolerance range for the mean Ohm value (in Ohms).

 Note: This version of the program has been updated to display color
 for TEXT for all four resistor bands.
*/

// to compile: gcc resistor.2.3d.c -lm -o resistor.2.3d

// 1/23/23 - Editor's Comment Area:

// C does not permit function declarations *inside* function declarations.
// So yellow() and reset() were moved *outside* main.

// Also, we need to put the *same number of variables* at the tail end of the printf
// statements as there are %s format specs in the "blah blah blahs"

// Added orange etc.

void yellow() {
 printf("\033[1;33m");
 }

void reset() {
 printf("\033[0m");
 }

int main()
{

yellow();
printf("\nresistor.2.3d.c - ceb/lrb\n" );
reset();

int b1,b2,m,t;   // m, t added for the multiplier, and tolerance bands

printf("\n           |-------------------------------------------------------|");
printf("\n           |   ||          ||         ||                      ||   |");
printf("\n           |   ||          ||         ||                      ||   |");
printf("\n     ------|   ||          ||         ||                      ||   |------");
printf("\n           |   ||          ||         ||                      ||   |");
printf("\n           |   ||          ||         ||                      ||   |");
printf("\n           |   ||          ||         ||                      ||   |");
printf("\n           |-------------------------------------------------------|");
printf("\n                                        \\                            ");
printf("\n                                         \\                 resistance");
printf("\n             band1        band2           \\                tolerance ");
printf("\n              1st          2nd                                           ");
printf("\n             digit       digit         multiplier                       ");
printf("\n                                                                         ");
printf("\n");
printf("\n          COLOR DIGIT   COLOR DIGIT   COLOR MULTIPLIER   COLOR TOLERANCE ");
printf("\n          -----------   -----------   ----------------   --------------- ");
printf("\n          %sBLACK%s   0     %sBLACK%s   0     %sBLACK%s          1   %sSILVER%s +-  10%% ",cd,r,cd,r,cd,r,c9,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sBROWN%s   1     %sBROWN%s   1     %sBROWN%s         10   %sGOLD%s   +-   5%% ",cb,r,cb,r,cb,r,ca,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sRED%s     2     %sRED%s     2     %sRED%s          100   %sBROWN%s  +-   1%% ",c1,r,c1,r,c1,r,cb,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sORANGE%s  3     %sORANGE%s  3     %sORANGE%s     1,000   %sRED%s    +-   2%% ",c8,r,c8,r,c8,r,c1,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sYELLOW%s  4     %sYELLOW%s  4     %sYELLOW%s    10,000   %sORANGE%s +-   3%% ",c3,r,c3,r,c3,r,c8,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sGREEN%s   5     %sGREEN%s   5     %sGREEN%s    100,000   %sGREEN%s  +- 0.5%% ",c2,r,c2,r,c2,r,c2,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sBLUE%s    6     %sBLUE%s    6     %sBLUE%s   1,000,000   %sBLUE%s   +- 0.25%% ",c4,r,c4,r,c4,r,c4,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sVIOLET%s  7     %sVIOLET%s  7     SILVER      0.01   %sVIOLET%s +- 0.1%%  ",c5,r,c5,r,c5,r);
printf("\n          --------------------------------------------------------------");
printf("\n          %sGREY%s    8     %sGREY%s    8     %sGOLD%s         0.1                   ",cc,r,cc,r,ca,r);
printf("\n          --------------------------------------------");
printf("\n          %sWHITE%s   9     %sWHITE%s   9                                        ",c7,r,c7,r);
printf("\n          -----------------------");
printf("\n");

printf("\nEnter band 1 (0 thru 9) : ");
scanf("%d",&b1);
printf("\nEnter band 2 (0 thru 9) : ");
scanf("%d",&b2);
printf("\nEnter band 3 (multiplier) (0 thru 8) : ");
scanf("%d",&m);
printf("\nEnter band 4 (tolerance) (0 thru 7) : ");
scanf("%d",&t);

float f,ft;

f=(float)(b1*10+b2);

if (m<7) f*=pow(10,m);
else f*=pow(10,m-9);

switch (t) {
 case 0 : {ft=10;break;}
 case 1 : {ft=5;break;}
 case 2 : {ft=1;break;}
 case 3 : {ft=2;break;}
 case 4 : {ft=3;break;}
 case 5 : {ft=.5;break;}
 case 6 : {ft=.25;break;}
 case 7 : {ft=.1;break;}
 }

printf("\n%2.2f Ohms tolerance +/-%2.2f %%\n",f,ft);

}


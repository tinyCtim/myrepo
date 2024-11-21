
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// four_way.c - 8/31/18 - lrb

// https://www.facebook.com/groups/299317782048/permalink/10156728266712049/

char * cdate(char *buff);
int rnd(int little,int big);
void ev(void);
void go(char *stripw);
void ra(void);
void disp(void);
void init(void);
unsigned int sleep(unsigned int seconds);
void showCursor(int show);

// arrival rate,head can move flag,elapsed time,seconds between
// frames,length of simulation

int ar,hm,etime,speed,ls;
char strip[20]; // holds 20 cars
int seed,last;

// heading west 43210 - strip 0
// heading south 98765 - strip 1
// heading east edcba - strip 2
// heading west jihgf - strip 3

// for now, we ignore what happens after a car travels through the
// intersection

void clrscr() {
#ifdef _WIN32
 system("cls");
#else
 system("clear");
#endif
 }

#define CON  "\x1b[?25h"
#define COFF "\x1b[?25l"

void showCursor(int show) {
 if (show) {
  fputs(CON,stdout);
  }
 else {
  fputs(COFF,stdout);
  }
 }

void init(void) {
 etime=0;
// get arrival rate
 printf("%carrival rate? (e.g. enter 4 for arrival probability of 3/4) ",10);
 scanf("%d",&ar);
// get speed
 printf("%cspeed ? (e.g. 1 is fast, 4 is slow) ",10);
 scanf("%d",&speed);
// get length of simulation
 printf("%clength of simulation? (e.g. 1300 time units) ",10);
 scanf("%d",&ls);
// space out array which holds 4 strips of 5 cars each
 int i;
 i=0;
 while (i<20) {strip[i]=' ';i=i+1;}
// seed the random number generator by hashing the seconds
 char datebuff[20];
 cdate(datebuff); // get the current date and time
// yyyy-mm-dd hh:mm:ss
// 0123456789abcdefghi
 int r1,r2;
 r1=datebuff[17]-'0';r2=datebuff[18]-'0';
 r1=10*r1+r2;
 if (r1%2==0) r1=r1+1; // make odd if even
 seed=last=r1;
 printf("%cfour_way.c - 8/31/18 - lrb",10);
 printf("%c%c%s%c",10,10,datebuff,10);
 sleep(5);
 showCursor(0);
 }

void disp(void) { // display intersection
 clrscr();
 int i;
 printf("%c%ctime %d%c",10,10,etime,10);
 i=5; // strip 1
 while (i<=9) {
 printf("%c      ",10);if (strip[i]=='x') printf("%c",'v');
  i=i+1;
  }
 printf("%c",10);
 i=4; // strip 0
 printf("%c      .. ",10);
 while (i>=0) {
  if (strip[i]=='x') printf("%c",'<');else printf("%c",' ');
  i=i-1;
  }
 i=10; // strip 2
 printf("%c",10);
 while (i<=14) {
  if (strip[i]=='x') printf("%c",'>');else printf("%c",' ');
  i=i+1;
  }
 printf(" ..");
 i=19; // strip 3
 printf("%c",10);
 while (i>=15) {
  printf("%c       ",10);if (strip[i]=='x') printf("%c",'^');
  i=i-1;
  }
 }

void ra(void) { // random arrival
// pick a random strip to process
 int r,s;
 s=rnd(0,3);
 r=rnd(1,ar);
 if (r!=ar) strip[s*5]='x'; // put a car at tail of strip
 }

void go(char *stripw) { // advance cars in strip
 int i;
 if (hm==1) {stripw[4]=' ';} // move head across intersection
 i=4;
 while (i>=0) {
// if there's a car to advance
  if (stripw[i-1]=='x') {
// if it can advance (i.e. nobody's in front of it)
   if (stripw[i]==' ') {
// advance it and space out the spot it occupied
    stripw[i]='x';
    stripw[i-1]=' ';
    }
   }
   i=i-1;
  }
 }

void ev(void) { // evolve i.e. move cars
 int s,found,save,sr;
// pick a random strip to process
 save=s=rnd(0,3);
 found=0;
 hm=0;
 while (found==0) { // 1
// any car at head of strip s?
  if (strip[s*5+4]=='x') {
// is head of strip to its right empty?
   sr=s+1;if (sr==4) sr=0;
   if (strip[sr*5+4]==' ') {found=1;hm=1;break;}
   }
  else {
   s=s+1;if (s==4) s=0;
   if (s==save) {found=2;break;}
   }
  } // 1
 if (found==1) { // use strip s
  go(strip+s*5);
  }
// no cars at head of strip can move so ...
 else { // 1 look for any strip that can move
  found=0;
  save=s=rnd(0,3);
  while (found==0) { // 2
   found=(strip[s*5+4]==' ') && (strip[s*5+3]=='x') || \
         (strip[s*5+3]==' ') && (strip[s*5+2]=='x') || \
         (strip[s*5+2]==' ') && (strip[s*5+1]=='x') || \
         (strip[s*5+1]==' ') && (strip[s*5+0]=='x');
   if (found!=0) { // use strip s
    go(strip+s*5);
    break;
    }
   else {
    s=s+1;if (s==4) s=0;
    if (s==save) {found=5;break;}
    }
   } // 2
   if (found==5) {printf("%cno forward motion possible",10);exit(1);}
  } // 1
 }

// load current date and time into supplied buff
char * cdate(char *buff) {
 time_t rawtime;
 struct tm *info;
 time(&rawtime);
 info=localtime(&rawtime);
 sprintf(buff,"%04d-%02d-%02d %02d:%02d:%02d", \
  info->tm_year-100+2000,info->tm_mon+1, \
  info->tm_mday,info->tm_hour,info->tm_min, \
  info->tm_sec);
 return buff;
 }

int rnd(int little,int big) {
 int range;
 if (last==0) last=seed=99;
 range=big-little+1;
 last=last*seed;
 if (last<0) last=-last;
 return little+(last/8)%range;
 }

int main(void) {
 init();
 while (etime<ls) {
// random arrival
  ra();
// display the intersection
  disp();
// pause a bit
   sleep(speed);
// evolve (i.e. move cars)
  ev();
  etime=etime+1;
  }
 showCursor(1);
 exit(0);
 }

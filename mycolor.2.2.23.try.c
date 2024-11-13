
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void red () {
  printf("\033[1;31m");
}

void yellow () {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}

void orange() {
  printf("\033[38;5;208m");
}

void mycolor(char *baz) {
  char foo[111];
  strcpy(foo,"\033[38;5;");
  char bar[11] = {0,0,0,0,0,0,0,0,0,0,0};
  strcpy(bar, foo);
  strcat(bar, baz);
  strcat(bar, "m");
  printf("%smycolor",bar);
}

int main (int argc, char *argv[]) {
  char c[3] = {0,0,0};
  if  (argc == 1) {;}
  else if (strcmp(argv[1], "-c") == 0) {
   strcpy(c, argv[2]);
   }
  else {
   printf("\nusage : ./mycolor [-c nnn]\n");
   exit(0);
   }
  red();
  printf("Hello ");
  yellow();
  printf("world");
  reset();
  orange();
  printf("!\n");
  reset();
  if (argc == 3) {
   mycolor(c);
   }
  reset();
  printf("\n");
  return 0;
}


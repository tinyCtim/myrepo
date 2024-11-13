// gcc -c library.c
// library.c

#include <stdio.h>

void show_pace(char str[], int seconds) {
	printf("%s %d:%d", str, seconds/60, seconds%60);
}

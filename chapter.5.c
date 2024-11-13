// chapter.5.c
// gcc chapter.5.c library.o -o chapter.5.exe

// ref: http://primepuzzle.com/lee-bradley/mini.challenges.html#5

#include <stdio.h>
#include "library.h"

int main(void)
{
	int seconds;
	printf("\nenter seconds ");
	scanf("%d",&seconds);
	show_pace("mm:ss", seconds);
	return 0;
}

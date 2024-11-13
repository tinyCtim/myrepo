#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 * chapter.4.c
 * 2/29/20 - lrb
 * ref: http://primepuzzle.com/lee-bradley/mini.challenges.html
 *
 * to compile
 *
 * gcc chapter.4.c -o chapter.4.exe (Windows)
 * gcc chapter.4.c -o chapter.4 (Linux)
 *
 * to run
 *
 * chapter.4.exe (Windows)
 * ./chapter.4 (Linux)
 *
 * read a line feed delimited text file and print each line on a new line
 *
 */

int main(void)
{
	printf("\nchapter.4.c - 2/29/20 - lrb\n");
	char *index;
	char *buffer[5000];
	char *filename[30];
	FILE *fp;
	printf("\nenter name of file to read : ");
	scanf("%s",&filename);
	if ((fp = fopen(filename,"r")) == NULL) {
		printf("\nerror on file open");exit(1);
	}
	fread(buffer,1,5000,fp);
	fclose(fp);
	printf("\n");
	while ((index = strchr(buffer,'\n')) != 0) {
		*index = 0;
		printf("%s\n",buffer);
		strcpy(buffer,++index);
	}
	exit(0);
}

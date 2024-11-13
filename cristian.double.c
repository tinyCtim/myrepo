// https://riptutorial.com/c/example/29223/read-lines-from-a-file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80

// read a line-delimited file of words and prints out the words
// with 3 double letters

// to compile: gcc cristian.double.c -o cristian.double
// to run: ./cristian.double "words.txt"

int main(int argc, char **argv)
{
    char *path;
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;

    if (argc < 1)
        return EXIT_FAILURE;
    path = argv[1];

    /* Open file */
    FILE *file = fopen(path, "r");

    if (!file)
    {
        perror(path);
        return EXIT_FAILURE;
    }

    int j,count;
    char work[20];
    printf("\ncristian.double.c - lrb - 2/8/22\n\n");

    /* Get each line until there are none left */
    while (fgets(line, MAX_LINE_LENGTH, file))
    {

        /* Add a trailing newline to lines that don't already have one */
        if (line[strlen(line) - 1] != '\n')
            printf("\n");

        strcpy(work,line);
        j=0;
        count=0;
        while (j<=strlen(work)-2) {
            if (work[j]==work[j+1]) count=count+1;
            j=j+1;
            }
        if (count==3) {
            printf("%s",work);
            }
   }

    /* Close file */
    if (fclose(file))
    {
        perror(path);
        return EXIT_FAILURE;
    }
}


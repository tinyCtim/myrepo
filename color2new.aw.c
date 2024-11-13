#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* color2new.c - 11/26/2022 - lrb - modified by aww */

void color(int color) // 0 to 7
{
    printf("\x1b[3%c;1m", '0' | color);
}

#define white() color(7)

int main(int argc, char *argv[])
{
    if (argc !=3) {
		puts("\ninvoke color2new.aw rounds sleep\n");
		exit(1);
		}
    int rounds = atoi(argv[1]);
    int s = atoi(argv[2]);
    int i, j;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));
    char linec[4] = "|-/\\";
    white();
    puts("\ncolor2new.c - 11/26/2022 - lrb\n");

    for (j = 1; j <= rounds; j++)
    {
        for (i = 1; i <= 1600; i++)
        {
            color(rand() & 7);
            putchar(linec[rand() & 3]); // line
            if (i % 100 == 0)
                putchar('\n');
        }
        white();
        printf("\nsleeping %d seconds\n\n", s);
        sleep(s);
    }

    white();
}


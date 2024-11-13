#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// /* color2new.c - 11/26/2022 - lrb - modified by aww */
// note: not threadsafe:
char linebuf[8] = "\x1b[3\x00;1m\x00";

// simple approach with stpcpy, which returns a pointer to end of string:
//#define writecolor(p,c,ch) (linebuf[3]=c|'0' , linebuf[7]=ch , p = stpcpy(p, linebuf))

// equivalent approach by "poking" a 64-bit integer all at once:
//#define writecolor(p,c,ch) (linebuf[3]=c|'0' , linebuf[7]=ch , *(long long *)p = *(long long *)linebuf , p+=8)

// Build a 64-bit integer, then write its bytes to the string at p. Shift c and ch into the appropriate bytes and bitwise-or them into place
#define writecolor(p,c,ch) ( *(long long *)p = (*(long long *)linebuf) | (((long long)c | '0') << 24) | ((long long)ch << 56), p+=8)

char * stpcpy(char * restrict dest, const char * restrict src);

int main(int argc, char *argv[])
{
    int i, j;
    time_t t;
    char buf[13000]; // at least 1600 * 8 + about 200
    /* Intializes random number generator */
    srand((unsigned)time(&t));
    char linec[9] = "|-/\\+*~%";
    puts("\x1b[2J\x1b[H\naww colorbuf - from color2new.c - 11/26/2022 - lrb");

    for (j = 1; j < 50; j++)
    {
        char *p=buf;
        p=stpcpy(p,"\x1b[5;0H");
        for (i = 1; i <= 1600; i++)
        {
            writecolor(p, rand() & 7, linec[rand() & 3]); 
            if (i % 100 == 0)
                *p++='\n'; 
        }
        writecolor(p,7,'\0');
        puts(buf);
        puts("\nsleeping 1 second\n");
        sleep(1);
    }
}


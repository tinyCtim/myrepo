#include <stdio.h>
#include <ctype.h>

/*
This program is from Dan Gookin's book Tiny C Projects

It reads text input and shifts every letter in the first half of the
alphabet ahead by 13 characters and every letter in the second half of
the alphabet 13 characters back.

3/23/22 - lrb - caesar01.c
*/

int main()
{
    int ch;

    while( (ch = getchar()) != EOF)
    {
        if( isalpha(ch))
        {
            if( toupper(ch)>='A' && toupper(ch)<='M')
                ch+= 13;
            else
                ch-= 13;
        }
        putchar(ch);
    }

    return(0);
}


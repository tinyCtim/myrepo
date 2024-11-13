// ref https://linux.die.net/man/3/localtime
// ref https://www.geeksforgeeks.org/time-h-localtime-function-in-c-with-examples/?ref=rp
// ref https://codegolf.stackexchange.com/questions/976/next-friday-the-13th
/// ^^ in case I want to modify this to read argv[] to comply with the code golf challenge
#include <stdio.h>
#include <time.h>
int main()
{
    struct tm* lt;
    time_t t = time(NULL);
    do {
        t += 86400;
        lt = localtime(&t);
    } while ( lt->tm_wday != 5 || lt->tm_mday != 13 );
    printf("Next Fri 13: %s\n", asctime(lt));
    return 0;
}
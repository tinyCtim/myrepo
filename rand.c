
// ref: https://stackoverflow.com/questions/5064379/generating-unique-random-numbers-in-c

/*
Here's a piece of code I used in answering a different question. It
maintains a list of numbers and, when it returns a random one to you, it
removes it from the list and decrements the count for the next random
selection.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ERR_NO_NUM -1
#define ERR_NO_MEM -2

int myRandom (int size) {
    int i,n;
    static int numNums = 0;
    static int *numArr = NULL;

    // Initialize with a specific size.

    if (size >= 0) {
        if (numArr != NULL)
            free (numArr);
        if ((numArr = malloc (sizeof(int) * size)) == NULL)
            return ERR_NO_MEM;
        for (i = 0; i < size; i++)
            numArr[i] = i;
        numNums = size;
    }

    // Error if no numbers left in pool.

    if (numNums == 0)
       return ERR_NO_NUM;

    // Get random number from pool and remove it (rnd in this
    // case returns a number between 0 and numNums-1 inclusive).

    n = rand() % numNums;
    i = numArr[n];
    numArr[n] = numArr[numNums-1];
    numNums--;
    if (numNums == 0) {
        free (numArr);
        numArr = 0;
    }

    return i;
}

int main (void) {
    int i;
    FILE *fp;
    fp = fopen("rand.out","w");
    char numstr[300-9] = {0};
    char str[10];
    srand (time (NULL));
    i = myRandom(100);
    sprintf(str, "%d", i);
    strcpy(numstr,str);strcat(numstr,"\n");
    while (i >= 0) {
      printf("%d ", i);
      i = myRandom (-1);
      if (i != -1) {
       sprintf(str, "%d", i);
       strcat(numstr,str);strcat(numstr,"\n");
       }
    }
    fwrite(numstr,1,sizeof(numstr)-1,fp);
    fclose(fp);
    printf("\n");
    return 0;
}

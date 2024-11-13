
// https://c-for-dummies.com/blog/?p=4946

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void scramble(char *p,int len)
{
	char *key;
	int x,r;

	/* allocate the temporary string and
	   fill with null characters */
	key = calloc( len+1, sizeof(char) );
	if( key==NULL )
	{
		fprintf(stderr,"Memory allocation error\n");
		exit(1);
	}

	/* process the string */
	x = 0;
	while(x<len)
	{
		r = rand() % len/2;		/* generate random value */
		if( !*(key+r*2) )		/* look for a null char */
		{
			*(key+r*2) = *(p+x);			/* assign the characters */
			*(key+r*2+1) = *(p+x+1);
			x = x+2;						/* increment the offset */
		}
	}

	/* update the scrambled string */
	strcpy( p, key);
}

int main()
{
	char sa[200];
	strcpy(sa,"000102030405060708091011121314151617181920212223242526272829");
	strcat(sa,"303132333435363738394041424344454647484950515253545556575859");
	strcat(sa,"606162636465666768697071727374757677787980818283848586878889");
	strcat(sa,"90919293949596979899");
	/* seed the randomizer */
	srand( (unsigned)time(NULL) );
	/* scramble the string */
	scramble(sa, strlen(sa));
	FILE *fp;
	fp=fopen("scramble.txt","w");
	fwrite(sa,1,sizeof(sa),fp);
	fclose(fp);
	return(0);
}


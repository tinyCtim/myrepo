#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	char names[10][100];
	int i,j;
	for(i=0;i < 5;i++) {
		printf("\nEnter a name which you want to register ");
		scanf("%s", names[i]);
	}
	printf("\n the names you entered were\n");
	for(i=0;i < 5;i++) printf("\n%s", names[i]);
	printf("\n");
}

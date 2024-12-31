
// secret_six.c - lrb - 9/4/24
// 9/6/24 9/20/24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFLEN 10000

int main(void)
{
	printf("\nsecret_six.c - lrb - 9/20/24\n");
	char source[MAXBUFLEN + 1] = "";
	char tource[MAXBUFLEN + 1] = "";
	char str[MAXBUFLEN + 1];
	char byte[2] = "";
	FILE *fp = fopen("secret_six_def.txt", "r"); // the number definition file
	FILE *fq = fopen("secret_six_encoded.txt", "r"); // the encoded file
	FILE *fr = fopen("secret_six_decoded.txt", "w"); // the decoded file
	fread(source, sizeof(char), MAXBUFLEN, fp);
	fread(tource, sizeof(char), MAXBUFLEN, fq);
	fclose(fp); fclose(fq);
	char key[20];
	char *pch;

/*

get bytes from the encoded file and put them to the decoded file. when a
numeric character is detected, collect the remaining numeric bytes in a
buffer, look up definition and put that definition in the decoded file.

*/

	int i = 0;
	int k;
	while(tource[i] != '\0') { // main loop
		if(tource[i] >= '0' && tource[i] <= '9') { // numeric?
			k = 0;
			key[k] = tource[i];
			key[k + 1] = '\0';
			i++;
			while(tource[i] >= '0' && tource[i] <= '9') {
				k++;
				key[k] = tource[i];
				key[k + 1] = '\0';
				i++;
				}
			strcpy(str, source);
			pch = strtok(str, " ");
			while(strcmp(pch, key) != 0) {
				pch = strtok(NULL, " ");
				if(pch == NULL) {
					printf("def not found");
					return 0;
					}
				}
			pch = strtok(NULL, " ");
			fwrite(pch, 1, strlen(pch), fr);
			} // if numeric
		byte[0] = tource[i];
		i++;
		fwrite(byte, 1, strlen(byte), fr);
		} // end main loop
	fclose(fr);
	printf("\ndecoded file written\n");
}

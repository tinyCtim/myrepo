
// sept.c - lrb - 9/10/24

/*

this program decodes an encoded file using a definition file that
has numbers and corresponding definitions

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFLEN 10000

int main(int argc, char *argv[])
{
	printf("\nsept.c - lrb - 9/10/24");
	printf("\nusage: sept [-d]\n");
	char source[MAXBUFLEN + 1] = "";
	char tource[MAXBUFLEN + 1] = "";
	char str[MAXBUFLEN + 1];
	char byte[2] = "";
	char def[30], encoded[30], decoded[30];
	int debug = 0;
	printf("\nName of definition file (e.g. foo.def) : ");
	fgets(def, 30, stdin);
	def[strlen(def)-1] = 0; // replace newline with 0
	printf("\nName of encoded file (e.g. foo.enc)) : ");
	fgets(encoded, 30, stdin);
	encoded[strlen(encoded)-1] = 0; // replace newline with 0
	printf("\nName of decoded file (e.g. foo.dec)) : ");
	fgets(decoded, 30, stdin);
	decoded[strlen(decoded)-1] = 0; // replace newline with 0
	if(argc == 2) debug = 1;
	FILE *fp = fopen(def, "r"); // the definition file
	FILE *fq = fopen(encoded, "r"); // the encoded file. NB! must end with an *
	FILE *fr = fopen(decoded, "w"); // the decoded file
	if(fp == NULL) {printf("\nerror on open of def file"); return 0;}
	if(fq == NULL) {printf("\nerror on open of encoded file"); return 0;}
	if(fr == NULL) {printf("\nerror on open of decoded file"); return 0;}
	fread(source, sizeof(char), MAXBUFLEN, fp);
	fread(tource, sizeof(char), MAXBUFLEN, fq);
	fclose(fp); fclose(fq);
	char key[20];
	char *pch;
	char delim[3]; delim[0]= ' '; delim[1] = 10; delim[2] = '\0';
/*

get bytes from the encoded file and put them to the decoded file. when a
numeric character is detected, collect the remaining numeric bytes in a
buffer, look up definition and put that definition in the decoded file.

*/

	int i = 0;
	int k;
	while(tource[i] != '*') { // main loop
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
			pch = strtok(str, delim);
			while(strcmp(pch, key) != 0) {
				pch = strtok(NULL, delim);
				if(pch == NULL) {
					printf("\ndef not found\n");
					return 0;
					}
				}
			pch = strtok(NULL, delim);
			fwrite(pch, 1, strlen(pch), fr);
			if(debug) printf("\npch is %s", pch);
			} // if numeric
		byte[0] = tource[i];
		i++;
		fwrite(byte, 1, strlen(byte), fr);
		if(debug) printf("\n%s", byte);
		} // end main loop
	fclose(fr);
	printf("\ndecoded file %s written\n\n",decoded);
	printf("\n");
	return 0;
}


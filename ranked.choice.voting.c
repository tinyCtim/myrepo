#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*

9/30/22 - 10/1,2/22 - lrb

10/6-9/22 - added file input

10/12,13,15/22 - names of input files from the terminal now, other fixes

10/19-21/22 - changed prompts and program name - added error on open
logic - added command tail processing

This program determines the most favored subjects chosen by people using
a ranked-choice voting system.

*/

int main(int argc, char **argv) {

 printf("\nranked.choice.voting.c - lrb - 10/21/22\n");

 FILE *fp;
 char fsubjects[30], fchoices[30];

 switch(argc) {
  case 5 :
   for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-c") == 0) strcpy(fchoices, argv[++i]); // 10/20/22
    if (strcmp(argv[i],"-s") == 0) strcpy(fsubjects, argv[++i]); // 10/20/22
    }
   break;
  case 1 :
   printf("\nEnter name of choices file (e.g. choices.txt) : ");
   scanf("%s",fchoices);
   printf("\nEnter name of subjects file (e.g. subjects.txt) : ");
   scanf("%s",fsubjects);
   break;
  default :
   printf("\nUsage: ranked.choice.voting [-c choices_file_name -s subjects_file_name]\n");
   exit(0);
  }

// votes[i][j] contains book # of ith voter, jth choice

 int votes[60][5];

 int book_num, books_left;
 int i, j, min_votes, loser, points;
 int num_voters = 0;
 int total_votes[60]; // 10/15/22

 char buffer[4000];
 char records[60][200], *idx;
 int record_count = 0, vote_count = 0;
 int cnt;

 fp = fopen(fsubjects, "r");
 if (fp == NULL) {printf("\nerror on open of %s", fsubjects); exit(1);}
 cnt = fread(buffer, 1, 4000, fp);
 printf("\n\n%d bytes read\n", cnt);
 fclose(fp);
 buffer[cnt] = 0;

 i = 0;
 while ((idx = strchr(buffer, '\n')) != 0) {
  *idx = 0;
  strcpy(records[i], buffer);
  strcpy(buffer, ++idx);
  printf("\n%s", records[i++]);
  }

 book_num = books_left = i-1;

 fp = fopen(fchoices, "r");
 if (fp == NULL) {printf("\nerror on open of %s", fchoices); exit(1);}
 cnt = fread(buffer, 1, 4000, fp);
 printf("\n\n%d bytes read\n", cnt);
 fclose(fp);
 buffer[cnt]=0;
 printf("\n%s\n",buffer);
 char work[4000];
 char *cdx;

 i=0;
 while ((idx = strchr(buffer, '\n')) != 0) {
  ++num_voters;
  *idx = 0;
  j = 0;
  strcpy(work, buffer);
  while ((cdx = strchr(work, ',')) != 0) {
   *cdx=0;
   votes[i][j] = atoi(work);
   strcpy(work, ++cdx);
   j++;
   }
  strcpy(buffer, ++idx);
  i++;
  }

 printf("\n\nnumber of voters = %d number of subjects = %d\n", num_voters, book_num);

 int how_many;
 printf("\nHow many subjects do you want to select? ");
 scanf("%d", &how_many);

 while (books_left > how_many) {

  for (i=0; i < book_num; i++) {
   total_votes[i] = 0;
   }

// total the votes

  for (i = 0; i < num_voters; i++) {
   points = 5;
   for (j = 0; j < 5; j++) { // 10/9/22
    if (strcmp(records[votes[i][j]], "eliminated") != 0) {
     total_votes[votes[i][j]] += points;
     points--;
     }
    }
   }

// determine the lowest total

  min_votes = 200;
  for (i = 0; i < book_num; i++) {
   if ((total_votes[i] < min_votes) && (strcmp(records[i], "eliminated") != 0)) {
    min_votes = total_votes[i];
    loser = i;
    }
   }

// eliminate the loser

  strcpy(records[loser], "eliminated");
  printf("\nloser = %d min_votes = %d", loser, min_votes);

  books_left--;

  }

// display the books that didn't get eliminated

 printf("\n\nAnd the winners are ...\n\n");

 for (i = 0; i < book_num; i++) {
  if (strcmp(records[i], "eliminated") != 0) {
   printf("%s got %d vote(s)\n", records[i], total_votes[i]);
   }
  }

 printf("\n");
 exit(0);
 }


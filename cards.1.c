#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

// gcc cards.1.c -lm

// cards.1.c - 2/17-19,21,25/24 3/6,7/24 - lrb
// ref: https://www.facebook.com/groups/299317782048/posts/10161684371582049/

/*
How many cards on average do you need to draw to get at least one of
each rank and one at least of each suit?
*/

int suits[4], ace_to_king[13];

char cardname[52][4] = {
 "AC","2C","3C","4C","5C","6C","7C","8C","9C","10C","JC","QC","KC",
 "AD","2D","3D","4D","5D","6D","7D","8D","9D","10D","JD","QD","KD",
 "AH","2H","3H","4H","5H","6H","7H","8H","9H","10H","JH","QH","KH",
 "AS","2S","3S","4S","5S","6S","7S","8S","9S","10S","JS","QS","KS"
 };

// used to determine if done
int sum() {
  int i, n = 0;
  for (i=0; i <= 3; i++) n += suits[i];
  for (i=0; i <= 12; i++) n += ace_to_king[i];
  return n == 17;
  }

int main() {
  float cnt[10000], average = 0, sum1 = 0, variance, std_deviation;
  time_t t;
  int cards[52], rnd, count, done, work, n, sim;
  sim = 5;
  int simulations = sim;
  int i = 0;
  srand((unsigned) time(&t));
  FILE *fp;
  fp = (fopen("cards.out", "w"));
  printf("\n\x1b[1mcards.1.c - lrb - 3/7/24\n");

  while (simulations--) { // outermost while

  printf("\n");
  // initialize arrays etc.
  count = done = 0;
  for (n = 0; n < 52; n++) cards[n] = 0;
  for (n = 0; n < 4; n++) suits[n] = 0;
  for (n = 0; n < 13; n++) ace_to_king[n] = 0;

  /* load 52 different random numbers in 0 .. 51 */
  while (count < 52) {
    rnd = rand() % 52;
    if (cards[rnd] == 0) {
      cards[rnd] = count;
      count++;
      }
    }

  count = 0;

  while (!done) {
    work = cards[count];	// select a random card
    if (work <= 12  || work >= 35)  printf("\x1b[30m"); //  Clubs and Spades are black
    else printf("\x1b[31m"); // Diamonds and Hearts are red
    printf("%s ", cardname[work]);
    suits[work / 13] = 1;	// update suits
    ace_to_king[work % 13] = 1;	// update ace_to_king
    done = sum();
    count++;
    }

  fprintf(fp, "%d\n", count);
  cnt[i++] = count;
  printf("\n");

  } // end outermost while

  for(i = 0; i < sim; i++) average += cnt[i];
  average /= sim;

  for (i = 0; i < sim; i++) sum1 += pow((cnt[i] - average), 2);

  variance = sum1 / (float) sim;
  std_deviation = sqrt(variance);

  printf("\n\naverage number of cards drawn was %2.4f\n", average);
  printf("\nstandard deviation %2.4f\n", std_deviation);

  fclose(fp);
  exit(0);
  }


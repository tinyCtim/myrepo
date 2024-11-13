#include "deck.h"
#include <iostream>
#include <unordered_set>

#define SAMPLES 100000L

using namespace std;

int main() {
  int numcards[SAMPLES]; //card count samples
  long sum = 0;
  double average; //average of all samples (the output of the program)
  Deck deck; //deck of cards
  Card card; //drawn card
  unordered_set<string> faces, suits; //keep track of which faces and suits were drawn
  
  for (int i = 0; i < SAMPLES; i++){
    deck.shuffleDeck();
    do{
      card = deck.dealCard();
     
      faces.insert(card.getFace()); //add face to set if not already there
      suits.insert(card.getSuit()); //add suit to set if not already there
        
    }while(faces.size() < 13 || suits.size() < 4); //keep drawing until one of each suit and face has been drawn

    numcards[i] = deck.getCurrentCard(); //how many cards were dealt before getting all suits and faces?

    faces.clear(); //reset for next sample
    suits.clear(); //reset for next sample
  }

  for (int i = 0; i < SAMPLES; i++){
    sum += numcards[i];
  }
  average = sum / (double) SAMPLES;
  cout << "The average number of cards dealt is " << average << endl;
  
  return 0;
} // main()


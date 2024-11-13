#include <string>

using namespace std;

class Card {
private:
  string face;
  string suit;

public:
  Card(string faceIn = "", string suitIn = "") {
    face = faceIn;
    suit = suitIn;
  } // constructor

  string toString() {
    return face + " of " + suit;
  }

  string getFace() { return face; }
  string getSuit() { return suit; }

}; // class Card

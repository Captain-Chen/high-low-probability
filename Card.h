#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card{
public:
  	Card();
	Card(int face, int suit);
	void setCard(int face, int suit);
  	string toString();
	int getSuit();
	int getFace();
private:
	int face;
  	int suit;
};

#endif

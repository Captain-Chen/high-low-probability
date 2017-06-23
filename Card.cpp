#include "Card.h"

Card::Card(){}

Card::Card(int face, int suit)
{
	setCard(face, suit);
}

void Card::setCard(int face, int suit){
    this->face = face;
    this->suit = suit;
}

int Card::getSuit()
{
	return suit;
}

int Card::getFace()
{
	return face;
}

string Card::toString(){
 	string suitName;
  	string faceName;
  
  	switch(suit)
    {
      case 1:
        suitName = "Clubs";
        break;
      case 2:
		suitName = "Diamonds";
        break;
      case 3:
		suitName = "Hearts";
        break;
      case 4:
        suitName = "Spades";
        break;
      default:
        suitName = to_string(suit);
    }
  
  	switch(face)
    {
      case 11:
        faceName = "Jack";
        break;
      case 12:
        faceName = "Queen";
        break;
      case 13:
        faceName = "King";
        break;
      default:
        faceName = to_string(face);
    }
	
      return faceName + " of " + suitName;
}


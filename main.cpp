#include "Card.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int method1(vector<Card> pickedCards, bool doPrint)
{
	// Clubs, Diamonds, Hearts, Spades
  	vector<int> cardSuit = {1, 2, 3, 4};
  	// Ace, 2-10, Jack, Queen, King
	vector<int> cardFace = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	// List to store cards
  	vector<Card> deck;
	// List to store seen cards
	vector<Card> seenDeck;
	// Card object
 	Card currentCard;
  	
  	// populate the deck
  	for(int i = 0; i < 52; i++)
    { 
      currentCard.setCard(cardFace[i % cardFace.size()], cardSuit[i % cardSuit.size()]);
      // add the card to the deck
      deck.push_back(currentCard);
	}
	
	int _cardFace, _cardSuit;
	unsigned int higher = 0, lower = 0, same = 0;
	double highProbability = 0, lowProbability = 0, sameProbability = 0;

	for(unsigned int x = 0; x < pickedCards.size(); x++)
	{ 
	//	cout << "1: Ace, 2-10, 11: Jack, 12: Queen, 13: King\n";
	//	cin >> _cardFace;
	//	cout << "1: Clubs, 2: Diamonds, 3: Hearts, 4: Spades\n";
	//	cin >> _cardSuit;
		_cardFace = pickedCards[x].getFace();
		_cardSuit = pickedCards[x].getSuit();

		// set the current card
		currentCard.setCard(_cardFace, _cardSuit);

		// iterate through the deck list. if the current card matches then remove it from the deck and add it to the seen list of cards
		for(vector<Card>::iterator iter = deck.begin(); iter != deck.end(); ++iter)
		{
			if(deck.empty())
			{
				break;
			}
			else if((*iter).getFace() == currentCard.getFace() && (*iter).getSuit() == currentCard.getSuit())
			{
				seenDeck.push_back((*iter));
				deck.erase(iter);
				break;
			}
		}

			// count the total number of higher, lower, or same valued cards
			for(vector<Card>::iterator iter = deck.begin(); iter != deck.end(); ++iter)
			{
				if((*iter).getFace() > currentCard.getFace())
				{
					++higher;
				}
				else if((*iter).getFace() < currentCard.getFace())
				{
					++lower;
				}
				else if((*iter).getFace() == currentCard.getFace())
				{
					++same;
				}
			}
			lowProbability = (double)lower / deck.size();
			highProbability = (double)higher / deck.size();
			sameProbability = (double)same / deck.size();

			if(doPrint)
			{
				cout << "\n\nCurrent card: " << currentCard.toString() << "\n";
				cout << "There are: " << deck.size() << " cards left in the deck\n";
				cout << "Probability of low card: " << lowProbability << '\n';
				cout << "Probability of high card: " << highProbability << '\n';
				cout << "Probability of same value card: " << sameProbability << '\n';
				cout << "Total probability (should add up to 1): " << lowProbability + highProbability + sameProbability << '\n';
			}	
				higher = lower = same = 0;
				lowProbability = highProbability = sameProbability = 0;
	}
}

void method2(vector<Card> pickedCards, bool doPrint)
{
	unsigned int deckSize = 52, suitCount = 4, cardsPerSuit = deckSize / suitCount;

	for(unsigned int i = 0; i < pickedCards.size(); i++)
	{
		Card currentCard = pickedCards[i];
		int curCardVal = currentCard.getFace(),
			curCardSuit = currentCard.getSuit();
		
			// these are the initial card counts as if no other cards had been picked yet
		int	higher = (cardsPerSuit - curCardVal) * suitCount,
			lower = deckSize - higher - suitCount,
			same = suitCount - 1;

			// determine the real card counts by comparing previously picked cards to this one
			for(unsigned int j = 0; j < i; j++)
			{
				Card otherCard = pickedCards[j];
				int oCardVal = otherCard.getFace(),
					oCardSuit = otherCard.getSuit();

				if(oCardVal == curCardVal)
				{
					// if it's the same exact card then skip
					if(oCardSuit == curCardSuit) continue;
					same--;
				}
				else if(oCardVal < curCardVal)
				{
					lower--;
				}
				else if(oCardVal > curCardVal)
				{
					higher--;
				}
			}
			int cardsLeft = deckSize - i - 1;
	}
}

typedef void (*cardFn)(vector<Card> pickedCards, bool doPrint);

double timeFn(cardFn fn, vector<Card> pickedCards)
{
	clock_t begin = clock();
	fn(pickedCards, false);
	clock_t end = clock();
	return double(end - begin) / CLOCKS_PER_SEC;
}

int main()
{
	vector<Card> pickedCards;
	for(int i = 0; i < 52; i++)
	{
		pickedCards.push_back(Card((i % 13) + 1, (i % 4) +1));
	}
	cout << "Method 1 run time: " << to_string(timeFn((cardFn)method1, pickedCards)) << " sec";
	cout << '\n';
	cout << "Method 2 run time: " << to_string(timeFn((cardFn)method2, pickedCards)) << " sec";
	return 0;
}

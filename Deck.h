#include <string>
#include <vector>
#include "Card.h"

#ifndef DECK_H
#define DECK_H

class cardStack
{
	friend class TexasHoldEm;

	public:
		cardStack();
		~cardStack();

		void printCards();

	protected:
		std::vector<Card*> deck;
};

class Deck : private cardStack
{
	public:
		Deck();
		~Deck();

		void shuffleDeck();
		Card* drawCard();

	private:
		int position{ 0 };
};

class Hand : public cardStack
{
	public:
		Hand() {}
		~Hand();

		void addCard(Card* card);
		void useCard(std::string card);
};

#endif
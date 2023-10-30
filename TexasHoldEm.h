#include <vector>
#include "Card.h"
#include "Deck.h"

#ifndef TEXASHOLDEM_H
#define TEXASHOLDEM_H

class TexasHoldEm
{
	public:
		TexasHoldEm();
		~TexasHoldEm();
		void dealCards();
		void dealTable();
		int evalHand(const int player);
		void findWinner();

	private:
		int numPlayers{ 2 };
		Deck myDeck;
		std::vector<Hand*> playerHands;
		std::vector<int> playerScores;
		Hand table;
};

#endif
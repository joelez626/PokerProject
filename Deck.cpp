#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "Card.h"
#include "Deck.h"

cardStack::cardStack()
{
}

cardStack::~cardStack()
{
	for (Card* card : deck)
	{
		delete card;
	}
}
Deck::~Deck()
{
}

Hand::~Hand()
{
}

void cardStack::printCards()
{
	for (Card* c : deck)
	{
		std::cout << c->printCard() << ' ';
	}
}

Deck::Deck()
{
	deck.reserve(52);
	for (int r = 2; r < 15; ++r)
	{
		for (int s = 0; s < 4; ++s)
		{
			deck.push_back(new Card(r, s));
		}
	}

	shuffleDeck();
}

void Deck::shuffleDeck()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

Card* Deck::drawCard()
{
	if (position >= deck.size())
	{
		std::cout << "Deck is empty!!!\n";
		return nullptr;
	}
	return deck[position++];
}

void Hand::addCard(Card* card)
{
	deck.push_back(new Card(card));
}

void Hand::useCard(std::string card)
{
	for (auto it = deck.begin(); it != deck.end(); ++it)
	{
		if ((*it)->printCard() == card)
		{
			delete *it;
			it = deck.erase(it);
			break;
		}
	}
}
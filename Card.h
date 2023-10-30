#include <string>

#ifndef CARD_H
#define CARD_H

class Card
{
    public:
        enum Rank
        {
            TWO = 2,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING,
            ACE
        };

        enum Suit
        {
            DIAMONDS,
            CLUBS,
            HEARTS,
            SPADES
        };

        Card(Rank r, Suit s);
        Card(int r, int s);
        Card(const Card* c);
        ~Card();

        Rank getRank();
        Suit getSuit();

        // There are no get methods because there is no need to change cards after they are set up

        // This gives the value of the card (e.g. JSpades > 10Diamond)
        int getValue();

        std::string printCard();


    private:
        Rank rank;
        Suit suit;
};

#endif
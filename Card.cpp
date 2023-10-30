#include <string>
#include "Card.h"

Card::Card(Rank r, Suit s)
    : rank{ r }
    , suit{ s }
{
}

Card::Card(int r, int s)
    : rank{ static_cast<Card::Rank>(r) }
    , suit{ static_cast<Card::Suit>(s) }
{
}

Card::Card(const Card* c)
{
    rank = c->rank;
    suit = c->suit;
}

Card::~Card()
{
}

Card::Rank Card::getRank()
{
    return rank;
}

Card::Suit Card::getSuit()
{
    return suit;
}

int Card::getValue()
{
    return rank * 4 + suit;
}

std::string Card::printCard()
{
    std::string rankStr{};
    std::string suitStr{};
    
    switch (rank)
    {
        case 11:
            rankStr = "J";
            break;
        case 12:
            rankStr = "Q";
            break;
        case 13:
            rankStr = "K";
            break;
        case 14:
            rankStr = "A";
            break;

        default:
            rankStr = std::to_string(rank);
    }

    switch (suit)
    {
        case DIAMONDS:
            suitStr = "D";
            break;
        case CLUBS:
            suitStr = "C";
            break;
        case HEARTS:
            suitStr = "H";
            break;
        case SPADES:
            suitStr = "S";
            break;
    }
    
    return rankStr + suitStr;
}
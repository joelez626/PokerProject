#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "TexasHoldEm.h"

void TexasHoldEm::dealCards()
{
    for (int i{ 0 }; i < numPlayers; ++i)
    {
        playerHands.push_back(new Hand{});

        // deal two cards
        playerHands[i]->addCard(myDeck.drawCard());
        playerHands[i]->addCard(myDeck.drawCard());

        std::cout << "Player " << i + 1 << " has the cards ";
        playerHands[i]->printCards();
        std::cout << '\n';
    }

}

void TexasHoldEm::dealTable()
{
    // deal the Flop (3 cards)
    // we do 5 cards for now as a simple case
    table.addCard(myDeck.drawCard());
    table.addCard(myDeck.drawCard());
    table.addCard(myDeck.drawCard());
    table.addCard(myDeck.drawCard());
    table.addCard(myDeck.drawCard());

    std::cout << "Cards on the table: ";
    table.printCards();
    std::cout << '\n';
}

int TexasHoldEm::evalHand(const int player)
{
    // store the number of cards according to suit / rank in bin
    
    std::vector<std::vector<int>> cards(4, std::vector<int>(15));
    
    

    for (Card* c : playerHands[player]->deck)
    {
        ++cards[c->getSuit()][c->getRank()];
    }
    for (Card* c : table.deck)
    {
        ++cards[c->getSuit()][c->getRank()];
    }
    
    

    std::vector<int> rankCount(15);
    std::vector<int> suitCount(4);

    for (int r{ 0 }; r < 15; ++r)
    {
        for (int s{ 0 }; s < 4; ++s)
        {
            if (cards[s][r])
            {
                ++rankCount[r];
                ++suitCount[s];
            }
        }
    }
  

    // 1. detect royal / straight flush
    for (int s{ 0 }; s < 4; ++s)
    {
        int count{ 0 };   // consecutive numbers of the same suit
        int highestRank{ 0 };

        if (cards[s][14])   // ACE can be counted as ONE in a straight
            ++count;

        for (int r{ 2 }; r < 15; ++r)
        {
            if (cards[s][r])   // card found
            {
                ++count;
                if (count >= 5)
                    highestRank = r;
            }
            else     // no card found
            {
                count = 0;
            }
        }

        if (highestRank == 14)
            return 90000000;    // royal flush
        
        if (highestRank != 0)
            return 80000000 + highestRank;  // straight flush
    }
    

    // 2. detect four of a kind
    for (int r{ 14 }; r >= 2; --r)
    {
        if (rankCount[r] == 4)
        {
            return 70000000 + r;
        }
    }

    // 3. detect full house
    for (int r{ 14 }; r >= 2; --r)
    {
        int highestTriple{ 0 };

        if (rankCount[r] == 3)
        {
            highestTriple = r;
            
            for (int rp{ 14 }; rp >= 2; --rp)
            {
                if (rankCount[rp] >= 2 && rp != highestTriple)
                {
                    return 60000000 + highestTriple;
                }
            }
        }
    }
    

    // 4. detect flush
    for (int s{ 0 }; s < 4; ++s)
    {
        if (suitCount[s] >= 5)
        {
            int cardScore{ 0 };
            
            for (int r{ 14 }, count{ 0 }; r >= 2 && count < 5; --r)
            {
                if (cards[s][r])
                {
                    // we can keep track of successive higher cards, each taking 4 bits (rank is between 2 to 14)
                    cardScore <<= 4;  
                    cardScore += r;
                    ++count;
                }
            }
            return 50000000 + cardScore;
        }
    }

    // 5. detect straight
    int count{ 0 };   // consecutive number count
    int highestRank{ 0 };
    
    if (rankCount[14])    // ACE can be counted as ONE in a straight
        ++count;
    
    for (int r{ 2 }; r < 15; ++r)
    {

        if (rankCount[r])   // card found
        {
            ++count;
            if (count >= 5)
                highestRank = r;
        }
        else     // no card found
        {
            count = 0;
        }


    }
    if (highestRank != 0)
    {
        return 40000000 + highestRank;
    }
    

    // 6. detect three of a kind
    for (int r{ 14 }; r >= 2; --r)
    {
        if (rankCount[r] == 3)
        {
            return 30000000 + r;    // r is the biggest triple
        }
    }
    

    // 7. detect two pair / pair / high card
    int highestPair{ 0 };
    int secondHighestPair{ 0 };
    
    for (int r{ 14 }; r >= 2; --r)
    {
        if (rankCount[r] == 2)
        {
            if (highestPair == 0)
                highestPair = r;
            else if (secondHighestPair == 0)
                secondHighestPair = r;
            else
                break;
        }
    }

    // two pair
    if (highestPair && secondHighestPair)
    {
        for (int rr{ 14 }; rr >= 2; --rr)
        {
            if (rankCount[rr] && rr != highestPair && rr != secondHighestPair)
            {
                return 20000000 + (highestPair << 8) + (secondHighestPair << 4) + rr;
            }
        }
    }
    
    // one pair
    else if (highestPair && !secondHighestPair)
    {
        int cardScore{ 0 };
        for (int rr{ 14 }, count{ 0 }; rr >= 2 && count < 3; --rr)
        {
            if (rankCount[rr] && rr != highestPair)
            {
                cardScore <<= 4;  // we can keep track of successive higher cards, each taking 4 bits (rank is between 2 to 14)
                cardScore += rr;
                ++count;
            }
        }
        return 10000000 + (highestPair << 12) + cardScore;
    }
    
    // high card
    else
    {
        int cardScore{ 0 };
        for (int rr{ 14 }, count{ 0 }; rr >= 2 && count < 5; --rr)
        {
            if (rankCount[rr])
            {
                cardScore <<= 4;  // we can keep track of successive higher cards, each taking 4 bits (rank is between 2 to 14)
                cardScore += rr;
                ++count;
            }
        }
        return cardScore;
    }
    
}

void TexasHoldEm::findWinner()
{
    int maxScore{ 0 };
    std::vector<int> winnerIndex;
    
    for (int i{ 0 }; i < numPlayers; ++i)
    {
        if (playerScores[i] > maxScore)
            maxScore = playerScores[i];
    }
    
    for (int i{ 0 }; i < numPlayers; ++i)
    {
        if (playerScores[i] == maxScore)
            winnerIndex.push_back(i);
    }

    if (winnerIndex.size() == 1)
    {
        std::cout << "The winner is Player " << winnerIndex[0] + 1;
    }
    else
    {
        std::cout << "The winners are ";
        for (int i{ 0 }; i < winnerIndex.size(); ++i)
        {
            std::cout << "Player " << winnerIndex[i] + 1;
            
            if (i != winnerIndex.size() - 1)
                std::cout << " and ";
        }
    }
    std::cout << " with ";

    int bestHandScore{ maxScore / 10000000 };
    switch (bestHandScore)
    {
        case 0:
            std::cout << "High Card.\n";
            break;
        case 1:
            std::cout << "One Pair.\n";
            break;
        case 2:
            std::cout << "Two Pair.\n";
            break;
        case 3:
            std::cout << "Three-of-a-Kind.\n";
            break;
        case 4:
            std::cout << "Straight.\n";
            break;
        case 5:
            std::cout << "Flush.\n";
            break;
        case 6:
            std::cout << "Full House.\n";
            break;
        case 7:
            std::cout << "Four-of-a-Kind.\n";
            break;
        case 8:
            std::cout << "Straight Flush.\n";
            break;
        case 9:
            std::cout << "Royal Flush.\n";
            break;
    }

}

TexasHoldEm::TexasHoldEm()
{
    Deck myDeck = Deck{};
    
    std::cout << "How many players are in the game? ";
    std::cin >> numPlayers;

    dealCards();
    dealTable();

    for (int i{ 0 }; i < numPlayers; ++i)
    {
        playerScores.push_back(evalHand(i));
        // std::cout << "Player " << i + 1 << " scored " << playerScores[i] << " points.\n";
    }
    
    findWinner();
}

TexasHoldEm::~TexasHoldEm()
{
    for (Hand* playerHand : playerHands)
    {
        delete playerHand;
    }
}
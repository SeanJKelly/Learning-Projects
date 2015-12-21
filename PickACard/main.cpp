// This program randomly picks a card from a deck and tells the user what it was

#include "stdafx.h"
#include <iostream>
#include <cstdlib>  //Contains srand()
#include <ctime>    //Contains time() for seeding the srand()
#include <string>   //Contains std::string

#include "deck.h"   //Contains all suits and ranks

// This function picks a random number between "min" and "max"
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);          // evenly distribute the random number across our range
}

// This function converts the enum supplied to it's string varient
std::string returnSuit(deck::Suits suit)
{
    switch (suit)
    {
        case deck::DIAMONDS:
            return "Diamonds";
        case deck::CLUBS:
            return "Clubs";
        case deck::SPADES:
            return "Spades";
        case deck::HEARTS:
            return "Hearts";
        default:
            return "Unable to parse";
    }
}

// This function converts the enum supplied to it's string varient
std::string returnRank(deck::Ranks rank)
{
    switch (rank)
    {
        case deck::ONE:
            return "One";
        case deck::TWO:
            return "Two";
        case deck::THREE:
            return "Three";
        case deck::FOUR:
            return "Four";
        case deck::FIVE:
            return "Five";
        case deck::SIX:
            return "Six";
        case deck::SEVEN:
            return "Seven";
        case deck::EIGHT:
            return "Eight";
        case deck::NINE:
            return "Nine";
        case deck::TEN:
            return "Ten";
        case deck::JACK:
            return "Jack";
        case deck::QUEEN:
            return "Queen";
        case deck::KING:
            return "King";
        case deck::ACE:
            return "Ace";
        default:
            return "Unable to parse";
    }
}

/* This function takes "suit" and "rank" (Which was given by getting a random
 * number and implicitly converting) and outputs the string names of the 
 * enumerations to the console, by using returnSuit() and returnRank()
 */
void outputResult(deck::Suits suit, deck::Ranks rank)
{
    std::cout << "I have picked the " << returnRank(rank) << " of " << returnSuit(suit) << "\n";
}

int main()
{
    using deck::Suits;
    using deck::Ranks;

    srand(static_cast<int>(time(0)));   // Seed our random number generator
    rand();                             // Discard the first result because rand() doesn't randomize the first random number very well in Visual Studio

    // First we need to grab a random suit and rank
    // We subtract the totals by one so we don't pick that enumerator by accedent
    Suits randomSuit = static_cast<Suits> (getRandomNumber(0, Suits::TOTAL_SUITS - 1));
    Ranks randomRank = static_cast<Ranks> (getRandomNumber(0, Ranks::TOTAL_RANKS - 1));

    outputResult(randomSuit, randomRank);
    return 0;
}


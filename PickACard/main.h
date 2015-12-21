#ifndef DECK_H
#define DECK_H

// Contains every card in a 52 card deck
// Rather use a namespace that explicitly convert enumerators to integers
// Enumerators don't take any memory until assigned to a variable!
namespace deck
{
    enum Suits
    {
        DIAMONDS,
        CLUBS,
        SPADES,
        HEARTS,
        TOTAL_SUITS
    };

    enum Ranks
    {
        ONE,
        TWO,
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
        ACE,
        TOTAL_RANKS
    };
}

#endif

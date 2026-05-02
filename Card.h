#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Card(Rank rank, Suit suit);
    
    Rank getRank() const;
    Suit getSuit() const;
    std::string getRankString() const;
    std::string getSuitString() const;
    std::string toString() const;

private:
    Rank rank;
    Suit suit;
};

#endif // CARD_H

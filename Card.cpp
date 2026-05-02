#include "Card.h"

Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

Card::Rank Card::getRank() const {
    return rank;
}

Card::Suit Card::getSuit() const {
    return suit;
}

std::string Card::getRankString() const {
    switch (rank) {
        case TWO: return "2";
        case THREE: return "3";
        case FOUR: return "4";
        case FIVE: return "5";
        case SIX: return "6";
        case SEVEN: return "7";
        case EIGHT: return "8";
        case NINE: return "9";
        case TEN: return "10";
        case JACK: return "J";
        case QUEEN: return "Q";
        case KING: return "K";
        case ACE: return "A";
        default: return "?";
    }
}

std::string Card::getSuitString() const {
    switch (suit) {
        case HEARTS: return "♥";
        case DIAMONDS: return "♦";
        case CLUBS: return "♣";
        case SPADES: return "♠";
        default: return "?";
    }
}

std::string Card::toString() const {
    return getRankString() + getSuitString();
}

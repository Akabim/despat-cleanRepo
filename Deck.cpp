#include "Deck.h"
#include <stdexcept>

void Deck::initialize() {
    cards.clear();
    for (int s = Card::HEARTS; s <= Card::SPADES; ++s) {
        for (int r = Card::TWO; r <= Card::ACE; ++r) {
            cards.push_back(Card(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)));
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::drawCard() {
    if (isEmpty()) {
        throw std::out_of_range("Deck is empty");
    }
    Card drawn = cards.back();
    cards.pop_back();
    return drawn;
}

int Deck::size() const {
    return cards.size();
}

bool Deck::isEmpty() const {
    return cards.empty();
}

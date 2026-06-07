#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;

public:
    void initialize();
    void shuffle();
    Card drawCard();
    int size() const;
    bool isEmpty() const;
};

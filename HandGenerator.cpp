#include "HandGenerator.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

Hand HandGenerator::generateHand() {
    std::cout << "Generating hand..." << std::endl;
    
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    
    std::vector<Card::Rank> ranks = {
        Card::TWO, Card::THREE, Card::FOUR, Card::FIVE, Card::SIX, Card::SEVEN,
        Card::EIGHT, Card::NINE, Card::TEN, Card::JACK, Card::QUEEN, Card::KING, Card::ACE
    };
    std::vector<Card::Suit> suits = {
        Card::HEARTS, Card::DIAMONDS, Card::CLUBS, Card::SPADES
    };

    std::vector<Card> deck;
    for (auto s : suits) {
        for (auto r : ranks) {
            deck.push_back(Card(r, s));
        }
    }

    std::shuffle(deck.begin(), deck.end(), rng);

    Hand hand;
    for (int i = 0; i < 5; ++i) {
        hand.cards.push_back(deck[i]);
    }

    return hand;
}

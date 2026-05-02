#include "FlushChecker.h"
#include <map>

std::string FlushChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::map<Card::Suit, int> suitCount;
    for (const auto& card : cards) {
        suitCount[card.getSuit()]++;
    }

    for (const auto& pair : suitCount) {
        if (pair.second >= 5) {
            return "Flush";
        }
    }

    return passToNext(cards);
}

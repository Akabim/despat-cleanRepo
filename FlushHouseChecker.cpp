#include "FlushHouseChecker.h"
#include <map>

std::string FlushHouseChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    std::map<Card::Suit, int> suitCount;

    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
        suitCount[card.getSuit()]++;
    }

    bool hasThree = false;
    bool hasPair = false;
    bool hasFlush = false;

    for (const auto& pair : rankCount) {
        if (pair.second >= 3) {
            hasThree = true;
        }
        else if (pair.second >= 2) {
            hasPair = true;
        }
    }

    for (const auto& pair : suitCount) {
        if (pair.second >= 5) {
            hasFlush = true;
            break;
        }
    }

    if (hasThree && hasPair && hasFlush) {
        return "Flush House";
    }

    return passToNext(cards);
}
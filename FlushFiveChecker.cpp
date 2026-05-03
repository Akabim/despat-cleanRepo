#include "FlushFiveChecker.h"
#include <map>

std::string FlushFiveChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    std::map<Card::Suit, int> suitCount;

    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
        suitCount[card.getSuit()]++;
    }

    bool hasFiveOfAKind = false;
    bool hasFlush = false;

    for (const auto& pair : rankCount) {
        if (pair.second >= 5) {
            hasFiveOfAKind = true;
            break;
        }
    }

    for (const auto& pair : suitCount) {
        if (pair.second >= 5) {
            hasFlush = true;
            break;
        }
    }

    if (hasFiveOfAKind && hasFlush) {
        return "Flush Five";
    }

    return passToNext(cards);
}
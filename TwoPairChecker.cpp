#include "TwoPairChecker.h"
#include <map>

std::string TwoPairChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 4) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
    }

    int pairCount = 0;
    for (const auto& pair : rankCount) {
        if (pair.second >= 2) {
            pairCount++;
        }
    }

    if (pairCount >= 2) {
        return "Two Pair";
    }

    return passToNext(cards);
}

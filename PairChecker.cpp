#include "PairChecker.h"
#include <map>

std::string PairChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 2) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
    }

    for (const auto& pair : rankCount) {
        if (pair.second >= 2) {
            return "Pair";
        }
    }

    return passToNext(cards);
}

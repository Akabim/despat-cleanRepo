#include "FourOfAKindChecker.h"
#include <map>

std::string FourOfAKindChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 4) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
    }

    for (const auto& pair : rankCount) {
        if (pair.second >= 4) {
            return "Four of a Kind";
        }
    }

    return passToNext(cards);
}

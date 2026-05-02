#include "ThreeOfAKindChecker.h"
#include <map>

std::string ThreeOfAKindChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 3) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
    }

    for (const auto& pair : rankCount) {
        if (pair.second >= 3) {
            return "Three of a Kind";
        }
    }

    return passToNext(cards);
}

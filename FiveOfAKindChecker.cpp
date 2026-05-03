#include "FiveOfAKindChecker.h"
#include <map>

std::string FiveOfAKindChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;

    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
    }

    for (const auto& pair : rankCount) {
        if (pair.second >= 5) {
            return "Five of a Kind";
        }
    }

    return passToNext(cards);
}
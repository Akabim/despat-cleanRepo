#include "FullHouseChecker.h"
#include <map>

std::string FullHouseChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::map<Card::Rank, int> rankCount;
    for (const auto& card : cards) {
        rankCount[card.getRank()]++;
    }

    bool hasThreeOfAKind = false;
    bool hasPair = false;

    for (const auto& pair : rankCount) {
        if (pair.second >= 3) hasThreeOfAKind = true;
        else if (pair.second >= 2) hasPair = true;
    }

    if (hasThreeOfAKind && hasPair) {
        return "Full House";
    }

    return passToNext(cards);
}

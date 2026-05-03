#include "StraightFlushChecker.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

std::string StraightFlushChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    if (isStraight(cards) && isFlush(cards)) {
        return "Straight Flush";
    }

    return passToNext(cards);
}

bool StraightFlushChecker::isFlush(const std::vector<Card>& cards) const {
    std::map<Card::Suit, int> suitCount;

    for (const auto& card : cards) {
        suitCount[card.getSuit()]++;
    }

    for (const auto& pair : suitCount) {
        if (pair.second >= 5) {
            return true;
        }
    }

    return false;
}

bool StraightFlushChecker::isStraight(const std::vector<Card>& cards) const {
    std::set<int> uniqueRanks;

    for (const auto& card : cards) {
        uniqueRanks.insert(static_cast<int>(card.getRank()));
    }

    if (uniqueRanks.count(Card::ACE)) {
        uniqueRanks.insert(1);
    }

    std::vector<int> ranks(uniqueRanks.begin(), uniqueRanks.end());
    std::sort(ranks.begin(), ranks.end());

    int consecutiveCount = 1;

    for (size_t i = 1; i < ranks.size(); i++) {
        if (ranks[i] == ranks[i - 1] + 1) {
            consecutiveCount++;

            if (consecutiveCount >= 5) {
                return true;
            }
        }
        else {
            consecutiveCount = 1;
        }
    }

    return false;
}
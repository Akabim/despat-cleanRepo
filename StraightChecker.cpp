#include "StraightChecker.h"
#include <set>
#include <vector>
#include <algorithm>

std::string StraightChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::set<int> uniqueRanks;

    for (const auto& card : cards) {
        uniqueRanks.insert(static_cast<int>(card.getRank()));
    }

    // Ace can also be used as rank 1 for A-2-3-4-5 straight
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
                return "Straight";
            }
        }
        else {
            consecutiveCount = 1;
        }
    }

    return passToNext(cards);
}
#include "StraightChecker.h"
#include <algorithm>
#include <set>

std::string StraightChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    std::vector<Card::Rank> ranks;
    for (const auto& card : cards) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    // Check for consecutive sequence (5 cards)
    if (ranks.size() >= 5) {
        bool isStraight = true;
        for (size_t i = 1; i < 5; i++) {
            if (ranks[i] != ranks[i-1] + 1) {
                isStraight = false;
                break;
            }
        }
        if (isStraight) {
            return "Straight";
        }
    }

    return passToNext(cards);
}

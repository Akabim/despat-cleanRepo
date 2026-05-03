#include "RoyalFlushChecker.h"
#include <algorithm>

std::string RoyalFlushChecker::checkHand(const std::vector<Card>& cards) {
    if (cards.size() < 5) {
        return passToNext(cards);
    }

    // Check if all cards have the same suit
    bool sameSuit = true;
    for (size_t i = 1; i < cards.size(); i++) {
        if (cards[i].getSuit() != cards[0].getSuit()) {
            sameSuit = false;
            break;
        }
    }

    if (!sameSuit) {
        return passToNext(cards);
    }

    // Check if cards are A, K, Q, J, 10
    std::vector<Card::Rank> ranks;
    for (const auto& card : cards) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    if (ranks.size() == 5 &&
        ranks[0] == Card::TEN &&
        ranks[1] == Card::JACK &&
        ranks[2] == Card::QUEEN &&
        ranks[3] == Card::KING &&
        ranks[4] == Card::ACE) {
        return "Royal Flush";
    }

    return passToNext(cards);
}

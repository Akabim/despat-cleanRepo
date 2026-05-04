#include "HandChecker.h"

void HandChecker::setNextChecker(HandChecker* next) {
    nextChecker = next;
}

std::string HandChecker::checkHand(const Hand& hand) {
    return checkHand(hand.cards);
}

std::string HandChecker::passToNext(const std::vector<Card>& cards) {
    if (nextChecker) {
        return nextChecker->checkHand(cards);
    }
    return "No Hand";
}
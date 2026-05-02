#include "HandChecker.h"

void HandChecker::setNextChecker(HandChecker* next) {
    nextChecker = next;
}

std::string HandChecker::passToNext(const std::vector<Card>& cards) {
    if (nextChecker != nullptr) {
        return nextChecker->checkHand(cards);
    }
    return "High Card";
}

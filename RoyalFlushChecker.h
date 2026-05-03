#ifndef ROYALFLUSHCHECKER_H
#define ROYALFLUSHCHECKER_H

#include "HandChecker.h"

class RoyalFlushChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // ROYALFLUSHCHECKER_H

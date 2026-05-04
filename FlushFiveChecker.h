#ifndef FLUSHFIVECHECKER_H
#define FLUSHFIVECHECKER_H

#include "HandChecker.h"

class FlushFiveChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif
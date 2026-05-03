#ifndef FLUSHCHECKER_H
#define FLUSHCHECKER_H

#include "HandChecker.h"

class FlushChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif
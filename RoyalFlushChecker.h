#ifndef ROYALFLUSHCHECKER_H
#define ROYALFLUSHCHECKER_H

#include "HandChecker.h"

class RoyalFlushChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // ROYALFLUSHCHECKER_H

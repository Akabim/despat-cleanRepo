#ifndef TWOPAIRCCHECKER_H
#define TWOPAIRCCHECKER_H

#include "HandChecker.h"

class TwoPairChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // TWOPAIRCCHECKER_H

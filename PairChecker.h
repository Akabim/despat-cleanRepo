#ifndef PAIRCCHECKER_H
#define PAIRCCHECKER_H

#include "HandChecker.h"

class PairChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // PAIRCCHECKER_H

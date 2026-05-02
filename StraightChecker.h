#ifndef STRAIGHTCHECKER_H
#define STRAIGHTCHECKER_H

#include "HandChecker.h"

class StraightChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // STRAIGHTCHECKER_H

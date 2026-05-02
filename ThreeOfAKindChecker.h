#ifndef THREEOFAKINDCHECKER_H
#define THREEOFAKINDCHECKER_H

#include "HandChecker.h"

class ThreeOfAKindChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // THREEOFAKINDCHECKER_H

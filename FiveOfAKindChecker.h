#ifndef FIVEOFAKINDCHECKER_H
#define FIVEOFAKINDCHECKER_H

#include "HandChecker.h"

class FiveOfAKindChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif
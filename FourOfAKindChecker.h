#ifndef FOUROFAKINDCHECKER_H
#define FOUROFAKINDCHECKER_H

#include "HandChecker.h"

class FourOfAKindChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // FOUROFAKINDCHECKER_H

#ifndef FULLHOUSECHECKER_H
#define FULLHOUSECHECKER_H

#include "HandChecker.h"

class FullHouseChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // FULLHOUSECHECKER_H

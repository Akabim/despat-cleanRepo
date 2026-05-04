#ifndef FLUSHHOUSECHECKER_H
#define FLUSHHOUSECHECKER_H

#include "HandChecker.h"

class FlushHouseChecker : public HandChecker {
public:
    using HandChecker::checkHand;
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif
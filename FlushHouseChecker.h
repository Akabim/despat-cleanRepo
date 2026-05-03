#ifndef FLUSHHOUSECHECKER_H
#define FLUSHHOUSECHECKER_H

#include "HandChecker.h"

class FlushHouseChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif
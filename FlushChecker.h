#ifndef FLUSCHCHECKER_H
#define FLUSCHCHECKER_H

#include "HandChecker.h"

class FlushChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // FLUSCHCHECKER_H

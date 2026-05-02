#ifndef HIGHCARDCHECKER_H
#define HIGHCARDCHECKER_H

#include "HandChecker.h"

class HighCardChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;
};

#endif // HIGHCARDCHECKER_H

#ifndef STRAIGHTFLUSHCHECKER_H
#define STRAIGHTFLUSHCHECKER_H

#include "HandChecker.h"

class StraightFlushChecker : public HandChecker {
public:
    std::string checkHand(const std::vector<Card>& cards) override;

private:
    bool isStraight(const std::vector<Card>& cards) const;
    bool isFlush(const std::vector<Card>& cards) const;
};

#endif
#ifndef HANDCHECKER_H
#define HANDCHECKER_H

#include "Card.h"
#include <vector>
#include <string>

class HandChecker {
public:
    virtual ~HandChecker() = default;
    
    virtual std::string checkHand(const std::vector<Card>& cards) = 0;
    
    void setNextChecker(HandChecker* next);
    
protected:
    HandChecker* nextChecker = nullptr;
    
    std::string passToNext(const std::vector<Card>& cards);
};

#endif // HANDCHECKER_H

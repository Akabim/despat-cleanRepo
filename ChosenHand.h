#pragma once
#include "Hand.h"
#include <string>

class ChosenHand {
private:
    Hand hand;
    std::string handType;

public:
    ChosenHand() = default;
    ChosenHand(const Hand& h, const std::string& type) : hand(h), handType(type) {}

    Hand getHand() const { return hand; }
    std::string getHandType() const { return handType; }
    
    void setHand(const Hand& h) { hand = h; }
    void setHandType(const std::string& type) { handType = type; }
};

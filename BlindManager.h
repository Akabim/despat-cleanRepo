#pragma once

#include "BlindState.h"
#include <memory>
#include <string>

class BlindManager {
private:
    int currentAnte;
    std::unique_ptr<BlindState> currentBlind;

public:
    BlindManager();

    int getCurrentAnte() const;
    std::string getCurrentBlindName() const;
    int getCurrentTargetScore() const;
    int getCurrentRewardMoney() const;

    void advanceToNextBlind();
    void displayCurrentBlind() const;
};
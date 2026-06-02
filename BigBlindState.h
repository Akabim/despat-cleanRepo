#pragma once

#include "BlindState.h"

class BigBlindState : public BlindState {
public:
    std::string getName() const override;
    int getTargetScore(int currentAnte) const override;
    int getRewardMoney() const override;
    std::unique_ptr<BlindState> createNextState(int& currentAnte) const override;
    std::unique_ptr<RewardCommand> createSkipReward() const override;
};
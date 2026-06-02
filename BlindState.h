#pragma once

#include <memory>
#include <string>

class RewardCommand;

class BlindState {
public:
    virtual ~BlindState() = default;

    virtual std::string getName() const = 0;
    virtual int getTargetScore(int currentAnte) const = 0;
    virtual int getRewardMoney() const = 0;

    virtual std::unique_ptr<BlindState> createNextState(int& currentAnte) const = 0;
    virtual std::unique_ptr<RewardCommand> createSkipReward() const = 0;
};
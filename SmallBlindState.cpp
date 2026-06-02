#include "SmallBlindState.h"
#include "RewardCommand.h"
#include "BigBlindState.h"

std::string SmallBlindState::getName() const {
    return "Small Blind";
}

int SmallBlindState::getTargetScore(int currentAnte) const {
    return 50 * currentAnte;
}

int SmallBlindState::getRewardMoney() const {
    return 3;
}

std::unique_ptr<BlindState> SmallBlindState::createNextState(int& currentAnte) const {
    return std::make_unique<BigBlindState>();
}

std::unique_ptr<RewardCommand> SmallBlindState::createSkipReward() const {
    return nullptr;
}
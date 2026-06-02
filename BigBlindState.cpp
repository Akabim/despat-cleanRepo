#include "BigBlindState.h"
#include "RewardCommand.h"
#include "BossBlindState.h"

std::string BigBlindState::getName() const {
    return "Big Blind";
}

int BigBlindState::getTargetScore(int currentAnte) const {
    return 450 * currentAnte;
}

int BigBlindState::getRewardMoney() const {
    return 4;
}

std::unique_ptr<BlindState> BigBlindState::createNextState(int& currentAnte) const {
    return std::make_unique<BossBlindState>();
}

std::unique_ptr<RewardCommand> BigBlindState::createSkipReward() const {
    return nullptr;
}
#include "BossBlindState.h"
#include "RewardCommand.h"
#include "SmallBlindState.h"

std::string BossBlindState::getName() const {
    return "Boss Blind";
}

int BossBlindState::getTargetScore(int currentAnte) const {
    return 600 * currentAnte;
}

int BossBlindState::getRewardMoney() const {
    return 5;
}

std::unique_ptr<BlindState> BossBlindState::createNextState(int& currentAnte) const {
    currentAnte++;
    return std::make_unique<SmallBlindState>();
}

std::unique_ptr<RewardCommand> BossBlindState::createSkipReward() const {
    return nullptr;
}
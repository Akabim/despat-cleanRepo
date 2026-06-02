#include "RewardFactory.h"
#include "BonusHandCommand.h"
#include "FreePlayingCardCommand.h"

std::unique_ptr<RewardCommand> RewardFactory::createReward(const std::string& type) {
    if (type == "BonusHand") {
        return std::make_unique<BonusHandCommand>();
    } else if (type == "FreeCard") {
        return std::make_unique<FreePlayingCardCommand>();
    }
    return nullptr;
}

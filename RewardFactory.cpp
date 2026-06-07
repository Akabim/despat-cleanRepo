#include "RewardFactory.h"
#include "BonusHandCommand.h"
#include "FreePlayingCardCommand.h"
#include "FreeJokerCommand.h"
#include "DoubleMoneyCommand.h"
#include "MegaBlindBuffCommand.h"

std::unique_ptr<RewardCommand> RewardFactory::createReward(const std::string& type) {
    if (type == "BonusHand") {
        return std::make_unique<BonusHandCommand>();
    } else if (type == "FreeCard") {
        return std::make_unique<FreePlayingCardCommand>();
    } else if (type == "FreeJoker") {
        return std::make_unique<FreeJokerCommand>();
    } else if (type == "DoubleMoney") {
        return std::make_unique<DoubleMoneyCommand>();
    } else if (type == "MegaBlindBuff") {
        return std::make_unique<MegaBlindBuffCommand>();
    }
    return nullptr;
}

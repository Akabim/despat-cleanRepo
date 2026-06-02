#pragma once
#include <memory>
#include <string>
#include "RewardCommand.h"

class RewardFactory {
public:
    static std::unique_ptr<RewardCommand> createReward(const std::string& type);
};

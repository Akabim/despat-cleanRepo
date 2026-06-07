#pragma once
#include "RewardCommand.h"

class DoubleMoneyCommand : public RewardCommand {
public:
    void execute(GameSessionState& state) override;
};

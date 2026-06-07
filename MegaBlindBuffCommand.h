#pragma once
#include "RewardCommand.h"

class MegaBlindBuffCommand : public RewardCommand {
public:
    void execute(GameSessionState& state) override;
};

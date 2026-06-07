#pragma once
#include "RewardCommand.h"

class FreeJokerCommand : public RewardCommand {
public:
    void execute(GameSessionState& state) override;
};

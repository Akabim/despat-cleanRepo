#pragma once
#include "GameSessionState.h"

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual void execute(GameSessionState& session) = 0;
};

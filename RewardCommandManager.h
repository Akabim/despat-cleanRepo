#pragma once
#include <vector>
#include <memory>
#include <map>
#include "RewardCommand.h"
#include "RewardTiming.h"

class RewardCommandManager {
private:
    std::map<RewardTiming, std::vector<std::unique_ptr<RewardCommand>>> pendingCommands;

public:
    void addCommand(RewardTiming timing, std::unique_ptr<RewardCommand> command);
    void executeCommands(RewardTiming timing, GameSessionState& session);
};

#include "RewardCommandManager.h"
#include <iostream>

void RewardCommandManager::addCommand(RewardTiming timing, std::unique_ptr<RewardCommand> command) {
    pendingCommands[timing].push_back(std::move(command));
}

void RewardCommandManager::executeCommands(RewardTiming timing, GameSessionState& session) {
    auto it = pendingCommands.find(timing);
    if (it != pendingCommands.end()) {
        std::cout << "[Manager] Executing rewards for timing: " << static_cast<int>(timing) << std::endl;
        for (auto& command : it->second) {
            command->execute(session);
        }
        pendingCommands.erase(it);
    }
}

#pragma once

class GameSessionState;

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual void execute(GameSessionState& session) = 0;
};
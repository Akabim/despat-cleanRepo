#pragma once
#include "IScoreObserver.h"
#include <memory>
#include <vector>

class JokerManager {
private:
    std::vector<std::unique_ptr<IScoreObserver>> jokers;

public:
    void addJoker(std::unique_ptr<IScoreObserver> joker);
    void applyJokers(ScoreContext& context);
    void displayJokers() const;
};
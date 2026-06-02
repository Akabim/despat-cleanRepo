#pragma once
#include "IJoker.h"
#include <memory>
#include <vector>

class JokerManager {
private:
    std::vector<std::unique_ptr<IJoker>> jokers;

public:
    void addJoker(std::unique_ptr<IJoker> joker);
    void applyJokers(ScoreContext& context);
    void displayJokers() const;
};
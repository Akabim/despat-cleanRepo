#pragma once
#include "IScoreObserver.h"

class StraightXMultJoker : public IScoreObserver {
public:
    std::string getName() const override;
    void update(ScoreContext& context) override;
};
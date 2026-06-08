#pragma once
#include "IScoreObserver.h"

class PairMultJoker : public IScoreObserver {
public:
    std::string getName() const override;
    void update(ScoreContext& context) override;
};
#pragma once
#include "IJoker.h"

class StraightXMultJoker : public IJoker {
public:
    std::string getName() const override;
    bool canActivate(const ScoreContext& context) const override;
    void apply(ScoreContext& context) override;
};
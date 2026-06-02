#include "StraightXMultJoker.h"

std::string StraightXMultJoker::getName() const {
    return "Straight XMult Joker";
}

bool StraightXMultJoker::canActivate(const ScoreContext& context) const {
    return context.getHandType() == "Straight" || context.getHandType() == "Straight Flush";
}

void StraightXMultJoker::apply(ScoreContext& context) {
    context.multiplyMult(2);
    context.addLog(getName() + " activated: x2 Mult because hand is Straight type");
}
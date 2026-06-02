#include "PairMultJoker.h"

std::string PairMultJoker::getName() const {
    return "Pair Joker";
}

bool PairMultJoker::canActivate(const ScoreContext& context) const {
    return context.getHandType() == "Pair" || context.getHandType() == "Two Pair";
}

void PairMultJoker::apply(ScoreContext& context) {
    context.addMult(8);
    context.addLog(getName() + " activated: +8 Mult because hand contains pair");
}
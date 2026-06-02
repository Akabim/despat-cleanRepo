#include "BasicMultJoker.h"

std::string BasicMultJoker::getName() const {
    return "Basic Joker";
}

bool BasicMultJoker::canActivate(const ScoreContext& context) const {
    return context.getHandType() != "No Hand";
}

void BasicMultJoker::apply(ScoreContext& context) {
    context.addMult(4);
    context.addLog(getName() + " activated: +4 Mult");
}
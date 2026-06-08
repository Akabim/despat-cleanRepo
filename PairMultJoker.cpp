#include "PairMultJoker.h"

std::string PairMultJoker::getName() const {
    return "Pair Joker";
}

void PairMultJoker::update(ScoreContext& context) {
    if (context.getHandType() == "Pair" || context.getHandType() == "Two Pair") {
        context.addMult(8);
        context.addLog(getName() + " activated: +8 Mult because hand contains pair");
    }
}
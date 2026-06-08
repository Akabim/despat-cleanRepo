#include "StraightXMultJoker.h"

std::string StraightXMultJoker::getName() const {
    return "Straight XMult Joker";
}

void StraightXMultJoker::update(ScoreContext& context) {
    if (context.getHandType() == "Straight" || context.getHandType() == "Straight Flush") {
        context.multiplyMult(2);
        context.addLog(getName() + " activated: x2 Mult because hand is Straight type");
    }
}
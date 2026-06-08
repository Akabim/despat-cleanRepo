#include "BasicMultJoker.h"

std::string BasicMultJoker::getName() const {
    return "Basic Joker";
}

void BasicMultJoker::update(ScoreContext& context) {
    if (context.getHandType() != "No Hand") {
        context.addMult(4);
        context.addLog(getName() + " activated: +4 Mult");
    }
}
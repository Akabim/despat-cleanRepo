#include "ScoreContext.h"

ScoreContext::ScoreContext(const Hand& hand, const std::string& handType, const HandScore& baseScore)
    : hand(hand), handType(handType), chips(baseScore.chips), mult(baseScore.mult) {
}

const Hand& ScoreContext::getHand() const {
    return hand;
}

std::string ScoreContext::getHandType() const {
    return handType;
}

int ScoreContext::getChips() const {
    return chips;
}

double ScoreContext::getMult() const {
    return mult;
}

double ScoreContext::getFinalScore() const {
    return chips * mult;
}

void ScoreContext::addChips(int amount) {
    chips += amount;
}

void ScoreContext::addMult(double amount) {
    mult += amount;
}

void ScoreContext::multiplyMult(double amount) {
    mult *= amount;
}

void ScoreContext::addLog(const std::string& message) {
    logs.push_back(message);
}

const std::vector<std::string>& ScoreContext::getLogs() const {
    return logs;
}
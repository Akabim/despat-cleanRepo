#pragma once
#include "Hand.h"
#include "HandScore.h"
#include <string>
#include <vector>

class ScoreContext {
private:
    Hand hand;
    std::string handType;
    int chips;
    double mult;
    std::vector<std::string> logs;

public:
    ScoreContext(const Hand& hand, const std::string& handType, const HandScore& baseScore);

    const Hand& getHand() const;
    std::string getHandType() const;
    int getChips() const;
    double getMult() const;
    double getFinalScore() const;

    void addChips(int amount);
    void addMult(double amount);
    void multiplyMult(double amount);

    void addLog(const std::string& message);
    const std::vector<std::string>& getLogs() const;
};
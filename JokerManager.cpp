#include "JokerManager.h"
#include <iostream>

void JokerManager::addJoker(std::unique_ptr<IScoreObserver> joker) {
    jokers.push_back(std::move(joker));
}

void JokerManager::applyJokers(ScoreContext& context) {
    for (const auto& joker : jokers) {
        joker->update(context);
    }
}

void JokerManager::displayJokers() const {
    if (jokers.empty()) {
        std::cout << "Active Jokers: None" << std::endl;
        return;
    }

    std::cout << "Active Jokers:" << std::endl;
    for (size_t i = 0; i < jokers.size(); ++i) std::cout << "+---------------+ ";
    std::cout << std::endl;

    for (const auto& joker : jokers) {
        std::string name = joker->getName();
        if (name.length() > 13) name = name.substr(0, 13);
        int pad = 13 - name.length();
        int leftPad = pad / 2;
        int rightPad = pad - leftPad;
        std::cout << "|" << std::string(leftPad, ' ') << name << std::string(rightPad, ' ') << "| ";
    }
    std::cout << std::endl;

    for (const auto& joker : jokers) {
        std::string tag = "  J O K E R  ";
        std::cout << "|" << tag << "| ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < jokers.size(); ++i) std::cout << "+---------------+ ";
    std::cout << std::endl;
}
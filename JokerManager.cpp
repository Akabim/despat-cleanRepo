#include "JokerManager.h"
#include <iostream>

void JokerManager::addJoker(std::unique_ptr<IJoker> joker) {
    jokers.push_back(std::move(joker));
}

void JokerManager::applyJokers(ScoreContext& context) {
    for (const auto& joker : jokers) {
        if (joker->canActivate(context)) {
            joker->apply(context);
        }
    }
}

void JokerManager::displayJokers() const {
    std::cout << "Active Jokers: ";

    if (jokers.empty()) {
        std::cout << "None";
    }

    for (const auto& joker : jokers) {
        std::cout << joker->getName() << " | ";
    }

    std::cout << std::endl;
}
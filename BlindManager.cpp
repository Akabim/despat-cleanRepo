#include "BlindManager.h"
#include "SmallBlindState.h"
#include <iostream>

BlindManager::BlindManager()
    : currentAnte(1), currentBlind(std::make_unique<SmallBlindState>()) {
}

int BlindManager::getCurrentAnte() const {
    return currentAnte;
}

std::string BlindManager::getCurrentBlindName() const {
    return currentBlind->getName();
}

int BlindManager::getCurrentTargetScore() const {
    return currentBlind->getTargetScore(currentAnte);
}

int BlindManager::getCurrentRewardMoney() const {
    return currentBlind->getRewardMoney();
}

void BlindManager::advanceToNextBlind() {
    currentBlind = currentBlind->createNextState(currentAnte);
}

void BlindManager::displayCurrentBlind() const {
    std::cout << "Ante: " << currentAnte << std::endl;
    std::cout << "Current Blind: " << getCurrentBlindName() << std::endl;
    std::cout << "Target Score: " << getCurrentTargetScore() << std::endl;
    std::cout << "Reward Money: $" << getCurrentRewardMoney() << std::endl;
}
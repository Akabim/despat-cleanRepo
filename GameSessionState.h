#pragma once
#include <vector>
#include "Card.h"

class GameSessionState {
private:
    int handsRemaining = 4;
    int discardsRemaining = 3;
    int money = 4;
    int ante = 1;
    bool isNextJokerFree = false;
    float blindScoreMultiplier = 1.0f;
    std::vector<Card> deck;

public:
    GameSessionState() {
        // Simple default deck setup if needed
    }

    int getHandsRemaining() const { return handsRemaining; }
    void setHandsRemaining(int hands) { handsRemaining = hands; }
    void addHandsRemaining(int amount) { handsRemaining += amount; }

    int getDiscardsRemaining() const { return discardsRemaining; }
    void setDiscardsRemaining(int discards) { discardsRemaining = discards; }
    void addDiscardsRemaining(int amount) { discardsRemaining += amount; }

    int getMoney() const { return money; }
    void addMoney(int amount) { money += amount; }

    int getAnte() const { return ante; }
    void setAnte(int a) { ante = a; }

    bool getIsNextJokerFree() const { return isNextJokerFree; }
    void setIsNextJokerFree(bool free) { isNextJokerFree = free; }

    float getBlindScoreMultiplier() const { return blindScoreMultiplier; }
    void setBlindScoreMultiplier(float mult) { blindScoreMultiplier = mult; }

    void addCardToDeck(const Card& card) {
        deck.push_back(card);
    }
    
    const std::vector<Card>& getDeck() const { return deck; }
};

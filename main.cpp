#include <iostream>
#include <vector>
#include <memory>

#include "Card.h"
#include "HandChecker.h"
#include "RoyalFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"
#include "FlushFiveChecker.h"
#include "FlushHouseChecker.h"
#include "FiveOfAKindChecker.h"
#include "StraightFlushChecker.h"
#include "HandGenerator.h"
#include "ChosenHand.h"

#include "HandScoreTable.h"
#include "ScoreContext.h"
#include "JokerManager.h"
#include "BasicMultJoker.h"
#include "PairMultJoker.h"
#include "StraightXMultJoker.h"

#include "BlindManager.h"

int main() {
    // Initialize chain of responsibility in order from highest to lowest hand
    FlushFiveChecker flushFiveChecker;
    FlushHouseChecker flushHouseChecker;
    FiveOfAKindChecker fiveOfAKindChecker;
    RoyalFlushChecker royalFlushChecker;
    StraightFlushChecker straightFlushChecker;
    FourOfAKindChecker fourOfAKindChecker;
    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;

    // Set up the chain
    flushFiveChecker.setNextChecker(&flushHouseChecker);
    flushHouseChecker.setNextChecker(&fiveOfAKindChecker);
    fiveOfAKindChecker.setNextChecker(&royalFlushChecker);
    royalFlushChecker.setNextChecker(&straightFlushChecker);
    straightFlushChecker.setNextChecker(&fourOfAKindChecker);
    fourOfAKindChecker.setNextChecker(&fullHouseChecker);
    fullHouseChecker.setNextChecker(&flushChecker);
    flushChecker.setNextChecker(&straightChecker);
    straightChecker.setNextChecker(&threeOfAKindChecker);
    threeOfAKindChecker.setNextChecker(&twoPairChecker);
    twoPairChecker.setNextChecker(&pairChecker);
    pairChecker.setNextChecker(&highCardChecker);

    std::cout << "=== Balatro Hand Checker + Joker System + Blind System ===" << std::endl;

    HandGenerator generator;

    // Initialize Joker system
    JokerManager jokerManager;
    jokerManager.addJoker(std::make_unique<BasicMultJoker>());
    jokerManager.addJoker(std::make_unique<PairMultJoker>());
    jokerManager.addJoker(std::make_unique<StraightXMultJoker>());

    jokerManager.displayJokers();
    std::cout << std::endl;

    // Initialize Blind progression system
    BlindManager blindManager;

    // Run randomized test 5 times
    for (int i = 1; i <= 5; ++i) {
        std::cout << "--- Run " << i << " ---" << std::endl;

        // Display current blind information
        blindManager.displayCurrentBlind();
        std::cout << std::endl;

        Hand hand = generator.generateHand();

        std::cout << "Cards: ";
        for (const auto& card : hand.cards) {
            std::cout << card.toString() << " ";
        }
        std::cout << std::endl;

        std::string result = flushFiveChecker.checkHand(hand);

        ChosenHand chosen(hand, result);

        std::cout << "Detected Hand: " << chosen.getHandType() << std::endl;

        // Get base hand score
        HandScore baseScore = HandScoreTable::getBaseScore(chosen.getHandType());

        // Create score context that can be modified by Jokers
        ScoreContext scoreContext(chosen.getHand(), chosen.getHandType(), baseScore);

        std::cout << "Base Score: "
            << scoreContext.getChips()
            << " Chips x "
            << scoreContext.getMult()
            << " Mult = "
            << scoreContext.getFinalScore()
            << std::endl;

        // Apply all active Jokers
        jokerManager.applyJokers(scoreContext);

        // Display Joker activation logs
        for (const auto& log : scoreContext.getLogs()) {
            std::cout << log << std::endl;
        }

        std::cout << "Final Score: "
            << scoreContext.getChips()
            << " Chips x "
            << scoreContext.getMult()
            << " Mult = "
            << scoreContext.getFinalScore()
            << std::endl;

        // Check blind result
        if (scoreContext.getFinalScore() >= blindManager.getCurrentTargetScore()) {
            std::cout << "Blind Cleared! Earned $"
                << blindManager.getCurrentRewardMoney()
                << std::endl;

            blindManager.advanceToNextBlind();
        }
        else {
            std::cout << "Blind Failed. Need "
                << blindManager.getCurrentTargetScore()
                << " score to clear this blind."
                << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
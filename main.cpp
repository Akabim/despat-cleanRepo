#include <iostream>
#include <vector>
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

    std::cout << "=== Balatro Hand Checker - Randomized Test ===" << std::endl;
    
    HandGenerator generator;
    
    for (int i = 1; i <= 5; ++i) {
        std::cout << "--- Run " << i << " ---" << std::endl;
        
        Hand hand = generator.generateHand();
        
        std::cout << "Cards: ";
        for (const auto& card : hand.cards) {
            std::cout << card.toString() << " ";
        }
        std::cout << std::endl;

        std::string result = flushFiveChecker.checkHand(hand);
        
        ChosenHand chosen(hand, result);
        
        std::cout << "Detected Hand: " << chosen.getHandType() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

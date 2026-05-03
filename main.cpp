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

int main() {
    // Initialize chain of responsibility in order from highest to lowest hand
    
    RoyalFlushChecker royalFlushChecker;
    FourOfAKindChecker fourOfAKindChecker;
    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;

    // Set up the chain
    royalFlushChecker.setNextChecker(&fourOfAKindChecker);
    fourOfAKindChecker.setNextChecker(&fullHouseChecker);
    fullHouseChecker.setNextChecker(&flushChecker);
    flushChecker.setNextChecker(&straightChecker);
    straightChecker.setNextChecker(&threeOfAKindChecker);
    threeOfAKindChecker.setNextChecker(&twoPairChecker);
    twoPairChecker.setNextChecker(&pairChecker);
    pairChecker.setNextChecker(&highCardChecker);

    std::cout << "=== Balatro Hand Checker - Chain of Responsibility Pattern ===" << std::endl;
    std::cout << "Status: Basic hands implemented. Waiting for special hand implementations." << std::endl;
    std::cout << std::endl;

    // Test cases
    std::cout << "=== Manual Test Cases ===" << std::endl;
    std::cout << std::endl;

    // Test 1: Royal Flush
    std::cout << "Test 1: Royal Flush" << std::endl;
    std::vector<Card> royalFlushCards = {
        Card(Card::TEN, Card::SPADES),
        Card(Card::JACK, Card::SPADES),
        Card(Card::QUEEN, Card::SPADES),
        Card(Card::KING, Card::SPADES),
        Card(Card::ACE, Card::SPADES)
    };
    std::cout << "Cards: ";
    for (const auto& card : royalFlushCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\nResult: " << royalFlushChecker.checkHand(royalFlushCards) << std::endl << std::endl;

    // Test 2: Four of a Kind
    std::cout << "Test 2: Four of a Kind" << std::endl;
    std::vector<Card> fourOfAKindCards = {
        Card(Card::SEVEN, Card::HEARTS),
        Card(Card::SEVEN, Card::DIAMONDS),
        Card(Card::SEVEN, Card::CLUBS),
        Card(Card::SEVEN, Card::SPADES),
        Card(Card::TWO, Card::HEARTS)
    };
    std::cout << "Cards: ";
    for (const auto& card : fourOfAKindCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\nResult: " << royalFlushChecker.checkHand(fourOfAKindCards) << std::endl << std::endl;

    // Test 3: Full House
    std::cout << "Test 3: Full House" << std::endl;
    std::vector<Card> fullHouseCards = {
        Card(Card::THREE, Card::HEARTS),
        Card(Card::THREE, Card::DIAMONDS),
        Card(Card::THREE, Card::CLUBS),
        Card(Card::NINE, Card::SPADES),
        Card(Card::NINE, Card::HEARTS)
    };
    std::cout << "Cards: ";
    for (const auto& card : fullHouseCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\nResult: " << royalFlushChecker.checkHand(fullHouseCards) << std::endl << std::endl;

    // Test 4: Flush
    std::cout << "Test 4: Flush" << std::endl;
    std::vector<Card> flushCards = {
        Card(Card::TWO, Card::CLUBS),
        Card(Card::FIVE, Card::CLUBS),
        Card(Card::SEVEN, Card::CLUBS),
        Card(Card::JACK, Card::CLUBS),
        Card(Card::KING, Card::CLUBS)
    };
    std::cout << "Cards: ";
    for (const auto& card : flushCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\nResult: " << royalFlushChecker.checkHand(flushCards) << std::endl << std::endl;

    return 0;
}

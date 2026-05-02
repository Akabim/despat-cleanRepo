#include <iostream>
#include <vector>
#include "Card.h"
#include "HandChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"

int main() {
    // Initialize chain of responsibility in order from highest to lowest hand
    // Current implemented: Flush > Straight > Three of a Kind > Two Pair > Pair > High Card
    
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;

    // Set up the chain
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

    // Test 1: Flush
    std::cout << "Test 1: Flush" << std::endl;
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
    std::cout << "\nResult: " << flushChecker.checkHand(flushCards) << std::endl << std::endl;

    // Test 2: Straight
    std::cout << "Test 2: Straight" << std::endl;
    std::vector<Card> straightCards = {
        Card(Card::NINE, Card::HEARTS),
        Card(Card::EIGHT, Card::DIAMONDS),
        Card(Card::SEVEN, Card::CLUBS),
        Card(Card::SIX, Card::SPADES),
        Card(Card::FIVE, Card::HEARTS)
    };
    std::cout << "Cards: ";
    for (const auto& card : straightCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\nResult: " << flushChecker.checkHand(straightCards) << std::endl << std::endl;

    // Test 3: Two Pair
    std::cout << "Test 3: Two Pair" << std::endl;
    std::vector<Card> twoPairCards = {
        Card(Card::TEN, Card::HEARTS),
        Card(Card::TEN, Card::DIAMONDS),
        Card(Card::FOUR, Card::CLUBS),
        Card(Card::FOUR, Card::SPADES),
        Card(Card::KING, Card::HEARTS)
    };
    std::cout << "Cards: ";
    for (const auto& card : twoPairCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\nResult: " << flushChecker.checkHand(twoPairCards) << std::endl << std::endl;

    return 0;
}

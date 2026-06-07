#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <cctype>

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
#include "GameSessionState.h"
#include "RewardCommandManager.h"
#include "RewardFactory.h"

Hand getDynamicInputHand() {
    Hand hand;
    std::string input;
    std::cout << "Masukkan 5 kartu (contoh: AH 10D 2S 5C 5H, dipisahkan spasi): ";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::string token;
    
    while (ss >> token && hand.cards.size() < 5) {
        if (token.length() < 2) continue;
        
        char suitChar = token.back();
        std::string rankStr = token.substr(0, token.length() - 1);
        
        Card::Suit suit;
        switch (toupper(suitChar)) {
            case 'H': suit = Card::HEARTS; break;
            case 'D': suit = Card::DIAMONDS; break;
            case 'C': suit = Card::CLUBS; break;
            case 'S': suit = Card::SPADES; break;
            default: continue;
        }
        
        Card::Rank rank;
        if (rankStr == "J" || rankStr == "j") rank = Card::JACK;
        else if (rankStr == "Q" || rankStr == "q") rank = Card::QUEEN;
        else if (rankStr == "K" || rankStr == "k") rank = Card::KING;
        else if (rankStr == "A" || rankStr == "a") rank = Card::ACE;
        else {
            int r = 0;
            try { r = std::stoi(rankStr); } catch(...) { continue; }
            if (r >= 2 && r <= 10) rank = static_cast<Card::Rank>(r);
            else continue;
        }
        
        hand.cards.push_back(Card(rank, suit));
    }
    
    // Jika format salah, isi sisa kartu dengan 2 Hearts
    while (hand.cards.size() < 5) {
        hand.cards.push_back(Card(Card::TWO, Card::HEARTS));
    }
    
    return hand;
}

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

    std::cout << "=== Balatro Hand Checker + Joker System + Blind System + Reward System ===" << std::endl;

    GameSessionState session;
    RewardCommandManager rewardManager;
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
    
    std::cout << std::endl;

    // Run randomized test 10 times
    for (int i = 1; i <= 10; ++i) {
        std::cout << "--- Run " << i << " ---" << std::endl;

        // Check for rewards at the start of a new blind/ante
        rewardManager.executeCommands(RewardTiming::NextBlind, session);

        // Display current blind information
        blindManager.displayCurrentBlind();
        std::cout << "Hands Remaining: " << session.getHandsRemaining() << std::endl;
        std::cout << std::endl;

        std::string action;
        std::cout << "Aksi (PLAY / SKIP)? ";
        std::getline(std::cin, action);

        if (action == "SKIP" || action == "skip") {
             std::cout << ">>> Decision: Player chooses to SKIP!" << std::endl;
             rewardManager.addCommand(RewardTiming::NextBlind, RewardFactory::createReward("BonusHand"));
             blindManager.advanceToNextBlind();
             std::cout << std::endl;
             continue;
        }

        Hand hand = getDynamicInputHand();

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
            session.setHandsRemaining(4); // Reset hands for next blind
        }
        else {
            session.addHandsRemaining(-1);
            if (session.getHandsRemaining() <= 0) {
                std::cout << "Game Over! Out of hands." << std::endl;
                break;
            }
            std::cout << "Remaining Hands: " << session.getHandsRemaining() << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
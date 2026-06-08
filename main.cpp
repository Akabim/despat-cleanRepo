#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "Card.h"
#include "Deck.h"
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

std::string getRankAscii(Card::Rank r) {
    if (r == Card::JACK) return "J";
    if (r == Card::QUEEN) return "Q";
    if (r == Card::KING) return "K";
    if (r == Card::ACE) return "A";
    return std::to_string(static_cast<int>(r));
}

std::string getSuitAscii(Card::Suit s) {
    switch (s) {
        case Card::HEARTS:   return "♥";
        case Card::DIAMONDS: return "♦";
        case Card::CLUBS:    return "♣";
        case Card::SPADES:   return "♠";
    }
    return "?";
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

    std::cout << "=== Balatro Simulator ===" << std::endl;

    GameSessionState session;
    RewardCommandManager rewardManager;

    // Initialize Joker system
    JokerManager jokerManager;
    // Jokers will be bought in the shop phase
    // jokerManager.displayJokers();
    std::cout << std::endl;

    BlindManager blindManager;

    bool gameOver = false;
    while (!gameOver) {
        rewardManager.executeCommands(RewardTiming::NextBlind, session);
        rewardManager.executeCommands(RewardTiming::EnterBlind, session);

        blindManager.displayCurrentBlind();
        if (session.getBlindScoreMultiplier() > 1.0f) {
            std::cout << "[BUFF AKTIF] Mega Blind Buff (Score x" << session.getBlindScoreMultiplier() << ")" << std::endl;
        }

        std::string action;
        std::cout << "Pilih Aksi Blind (PLAY / SKIP)? ";
        if (!std::getline(std::cin, action)) break;

        if (action == "SKIP" || action == "skip") {
             std::cout << ">>> Decision: Player chooses to SKIP!" << std::endl;
             std::cout << ">>> Mendapatkan 3 Skip Rewards dari Tugas Design Pattern!" << std::endl;
             
             rewardManager.addCommand(RewardTiming::EnterShop, RewardFactory::createReward("FreeJoker"));
             rewardManager.addCommand(RewardTiming::EnterShop, RewardFactory::createReward("DoubleMoney"));
             rewardManager.addCommand(RewardTiming::EnterBlind, RewardFactory::createReward("MegaBlindBuff"));
             
             blindManager.advanceToNextBlind();
             std::cout << std::endl;
             continue;
        }

        // --- PLAY PHASE ---
        session.setHandsRemaining(4);
        session.setDiscardsRemaining(3);
        float currentBlindScore = 0.0f;
        float targetScore = blindManager.getCurrentTargetScore();

        Deck deck;
        deck.initialize();
        deck.shuffle();

        std::vector<Card> currentHand;
        auto drawUpTo8 = [&]() {
            bool drawn = false;
            while (currentHand.size() < 8 && !deck.isEmpty()) {
                currentHand.push_back(deck.drawCard());
                drawn = true;
            }
            if (drawn) {
                std::sort(currentHand.begin(), currentHand.end(), [](const Card& a, const Card& b) {
                    if (a.getRank() != b.getRank()) return a.getRank() > b.getRank(); // Descending by rank
                    return a.getSuit() > b.getSuit();
                });
            }
        };
        drawUpTo8();

        bool blindCleared = false;

        while (session.getHandsRemaining() > 0 && !blindCleared) {
            std::cout << "\n=== TANGANMU ===" << std::endl;
            
            for (size_t i = 0; i < currentHand.size(); ++i) std::cout << ".-------. ";
            std::cout << "\n";
            
            for (size_t i = 0; i < currentHand.size(); ++i) {
                std::string rStr = getRankAscii(currentHand[i].getRank());
                if (rStr.length() == 1) rStr += " ";
                std::cout << "| " << rStr << "    | ";
            }
            std::cout << "\n";

            for (size_t i = 0; i < currentHand.size(); ++i) {
                std::cout << "|   " << getSuitAscii(currentHand[i].getSuit()) << "   | ";
            }
            std::cout << "\n";

            for (size_t i = 0; i < currentHand.size(); ++i) {
                std::string rStr = getRankAscii(currentHand[i].getRank());
                if (rStr.length() == 1) rStr = " " + rStr;
                std::cout << "|    " << rStr << " | ";
            }
            std::cout << "\n";

            for (size_t i = 0; i < currentHand.size(); ++i) std::cout << "'-------' ";
            std::cout << "\n";

            for (size_t i = 0; i < currentHand.size(); ++i) {
                std::cout << "   [" << (i+1) << "]    ";
            }
            std::cout << "\n";

            std::cout << "\nPlays: " << session.getHandsRemaining() << " | Discards: " << session.getDiscardsRemaining() << std::endl;
            std::cout << "Skor Saat Ini: " << currentBlindScore << " / " << targetScore << std::endl;
            
            std::cout << "Aksi (Contoh: 'P 1 2 3' untuk Play, 'D 1 2' untuk Discard): ";
            std::string moveInput;
            if (!std::getline(std::cin, moveInput)) break;

            if (moveInput.empty()) continue;

            char moveType = toupper(moveInput[0]);
            std::stringstream ss(moveInput.substr(1));
            std::vector<int> indices;
            int idx;
            while (ss >> idx) {
                if (idx >= 1 && idx <= currentHand.size()) {
                    indices.push_back(idx - 1);
                }
            }

            if (indices.empty()) continue;

            // Remove duplicates and sort descending
            std::sort(indices.rbegin(), indices.rend());
            indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

            if (moveType == 'D') {
                if (session.getDiscardsRemaining() <= 0) {
                    std::cout << "Sisa Discard habis!" << std::endl;
                    continue;
                }
                
                for (int i : indices) {
                    currentHand.erase(currentHand.begin() + i);
                }
                session.addDiscardsRemaining(-1);
                drawUpTo8();
                continue;
            } 
            else if (moveType == 'P') {
                if (indices.size() > 5) {
                    std::cout << "Hanya bisa play maksimal 5 kartu!" << std::endl;
                    continue;
                }

                Hand playedHand;
                for (int i : indices) {
                    playedHand.cards.push_back(currentHand[i]);
                }

                for (int i : indices) {
                    currentHand.erase(currentHand.begin() + i);
                }
                session.addHandsRemaining(-1);

                // Evaluate
                std::string result = flushFiveChecker.checkHand(playedHand);
                ChosenHand chosen(playedHand, result);
                std::cout << "Detected Hand: " << chosen.getHandType() << std::endl;

                HandScore baseScore = HandScoreTable::getBaseScore(chosen.getHandType());
                ScoreContext scoreContext(chosen.getHand(), chosen.getHandType(), baseScore);
                
                jokerManager.applyJokers(scoreContext);
                
                for (const auto& log : scoreContext.getLogs()) {
                    std::cout << ">>> [JOKER] " << log << std::endl;
                }
                
                float actualFinalScore = scoreContext.getFinalScore() * session.getBlindScoreMultiplier();
                std::cout << "Score didapatkan: " << actualFinalScore << std::endl;

                currentBlindScore += actualFinalScore;

                if (currentBlindScore >= targetScore) {
                     blindCleared = true;
                } else {
                     drawUpTo8();
                }
            }
        }

        if (blindCleared) {
            std::cout << "Blind Cleared! Earned $" << blindManager.getCurrentRewardMoney() << std::endl;
            session.addMoney(blindManager.getCurrentRewardMoney());

            std::cout << "\n=== SHOP PHASE ===" << std::endl;
            std::cout << "Uang sebelum Shop: $" << session.getMoney() << std::endl;
            rewardManager.executeCommands(RewardTiming::EnterShop, session);
            std::cout << "Uang setelah trigger EnterShop: $" << session.getMoney() << std::endl;

            bool shopActive = true;
            while (shopActive) {
                std::cout << "\nUangmu: $" << session.getMoney() << std::endl;
                if (session.getIsNextJokerFree()) {
                    std::cout << "[Shop] Voucher aktif: Joker berikutnya GRATIS!" << std::endl;
                }
                std::cout << "Daftar Joker yang bisa dibeli:" << std::endl;
                int priceBasic = session.getIsNextJokerFree() ? 0 : 4;
                int pricePair = session.getIsNextJokerFree() ? 0 : 6;
                int priceStraight = session.getIsNextJokerFree() ? 0 : 8;

                std::cout << "+---------------+  +---------------+  +---------------+" << std::endl;
                std::cout << "| 1. BASIC      |  | 2. PAIR       |  | 3. STRAIGHT   |" << std::endl;
                std::cout << "|    JOKER      |  |    JOKER      |  |    JOKER      |" << std::endl;
                std::cout << "|    $" << priceBasic << "         |  |    $" << pricePair << "         |  |    $" << priceStraight << "         |" << std::endl;
                std::cout << "+---------------+  +---------------+  +---------------+" << std::endl;
                
                std::cout << "0. Lanjut ke Blind Berikutnya" << std::endl;
                std::cout << "Pilih Joker untuk dibeli (0-3): ";
                
                std::string shopInput;
                if (!std::getline(std::cin, shopInput)) break;
                
                if (shopInput == "0") {
                    shopActive = false;
                } else if (shopInput == "1" || shopInput == "2" || shopInput == "3") {
                    int price = 0;
                    if (shopInput == "1") price = priceBasic;
                    else if (shopInput == "2") price = pricePair;
                    else if (shopInput == "3") price = priceStraight;

                    if (session.getMoney() >= price) {
                        session.addMoney(-price);
                        if (session.getIsNextJokerFree()) {
                            session.setIsNextJokerFree(false);
                        }
                        
                        if (shopInput == "1") jokerManager.addJoker(std::make_unique<BasicMultJoker>());
                        else if (shopInput == "2") jokerManager.addJoker(std::make_unique<PairMultJoker>());
                        else if (shopInput == "3") jokerManager.addJoker(std::make_unique<StraightXMultJoker>());
                        
                        std::cout << ">>> Pembelian Berhasil!" << std::endl;
                        jokerManager.displayJokers();
                    } else {
                        std::cout << ">>> Uang tidak cukup!" << std::endl;
                    }
                } else {
                    std::cout << ">>> Input tidak valid." << std::endl;
                }
            }
            std::cout << "==================\n" << std::endl;

            blindManager.advanceToNextBlind();
            session.setBlindScoreMultiplier(1.0f); // consume buff
        } else {
            std::cout << "Game Over! You didn't reach the target score." << std::endl;
            gameOver = true;
        }
    }
    return 0;
}
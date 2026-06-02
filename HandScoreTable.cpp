#include "HandScoreTable.h"

HandScore HandScoreTable::getBaseScore(const std::string& handType) {
    if (handType == "High Card") return HandScore(5, 1);
    if (handType == "Pair") return HandScore(10, 2);
    if (handType == "Two Pair") return HandScore(20, 2);
    if (handType == "Three of a Kind") return HandScore(30, 3);
    if (handType == "Straight") return HandScore(30, 4);
    if (handType == "Flush") return HandScore(35, 4);
    if (handType == "Full House") return HandScore(40, 4);
    if (handType == "Four of a Kind") return HandScore(60, 7);
    if (handType == "Straight Flush") return HandScore(100, 8);
    if (handType == "Royal Flush") return HandScore(100, 8);
    if (handType == "Five of a Kind") return HandScore(120, 12);
    if (handType == "Flush House") return HandScore(140, 14);
    if (handType == "Flush Five") return HandScore(160, 16);

    return HandScore(0, 1);
}
#pragma once
#include "HandScore.h"
#include <string>

class HandScoreTable {
public:
    static HandScore getBaseScore(const std::string& handType);
};
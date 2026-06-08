#pragma once
#include "ScoreContext.h"
#include <string>

class IScoreObserver {
public:
    virtual ~IScoreObserver() = default;
    virtual std::string getName() const = 0;
    virtual void update(ScoreContext& context) = 0;
};
